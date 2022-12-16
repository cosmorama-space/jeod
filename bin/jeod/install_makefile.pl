#!perl -w
################################################################################
#
# Purpose:
#   (Generate a makefile in a JEOD subdirectory or model directory)
#
#  
#
################################################################################

use strict;
use Getopt::Long;
use Cwd qw(abs_path cwd);

sub get_directories();
sub parse_overrides();
sub create_makefile_header();
sub generate_cflags_options();
sub create_subdir_makefile_targets();
sub create_model_makefile_targets();
sub generate_rules ($$$$;@);
sub update_file($$);
sub makefile_needs_update($$);

my ($Cwd,

    $Analysis,        # -analysis        Build in tools/analysis
    $Compiler,        # -compiler        Compiler (defaults to g++)
    $Extras,          # -extras          Build in unsupported/models
    $Gcov,            # -gcov            Compile with options for gcov
    $Harness,         # -harness         Build in tools/test_harness
    $Makefile,        # -makefile <name> Specify the makefile name
    $Non_trick,       # -nontrick        Build in unsupported/non_trick
    $Suffix,          # -suffix <value>  Specify the lib & obj directory suffix
    $Top,             # -top             Install the toplevel makefile
    $Trick,           # -trick           Build with -DTRICK_VER set


    @Install_options, # Options passed to install_makefile.pl
    @Subdirs,         # Directories passed to install_makefile.pl

    $Is_modeldir,
    $JEOD_models,
    $JEOD_libdir,
    $JEOD_objdir,
    $Rel,
    $Dir,
    $Reldir,
    $script,
    @Text,
    @Srcdirs,
    @Initial_overrides,
    @Final_overrides,
    %Override_targets);

die 'JEOD_HOME not defined' unless defined $ENV{JEOD_HOME};
die 'ER7_UTILS_HOME not defined' unless defined $ENV{ER7_UTILS_HOME};

$Cwd  = cwd();
($script = $0) =~ s/.*\//\$(JEOD_BIN)\//;


# Parse the command line: [options] <makefile> [non-top arguments]

$Analysis     = 0;
$Compiler     = 'g++';
$Extras       = 0;
$Gcov         = 0;
$Harness      = 1;
$Non_trick    = 0;
$Top          = 0;
$Trick        = 0;
$Suffix       = '';
$Makefile     = 'makefile';


$Is_modeldir    = 0;

GetOptions (
   'analysis!'    => \$Analysis,
   'compiler=s'   => \$Compiler,
   'extras!'      => \$Extras,
   'gcov!'        => \$Gcov,
   'harness!'     => \$Harness,
   'makefile=s'   => \$Makefile,
   'non_trick!'   => \$Non_trick,
   'suffix=s'     => \$Suffix,
   'top'          => \$Top,
   'trick!'       => \$Trick)
   or die "Syntax: perl $0 [options] arguments ... \n";

if ($Top) {
   $Rel      = '';
   $Dir      = '.';
   $Reldir   = '';
} else {
   scalar @ARGV >= 2 or die "Wrong number of arguments to $script";
   $Rel      = shift;
   $Dir      = shift;
   $Reldir   = $Rel eq '' ? $Dir : "$Rel/$Dir";
   die if $Dir eq '';
}
@Subdirs = @ARGV;


@Install_options = ('-makefile', $Makefile,
                    '-suffix', $Suffix,
                    '-compiler', $Compiler);
if ($Reldir !~ /\//) {
   push @Install_options, '-analysis' if $Analysis;
   push @Install_options, '-harness'  if $Harness;
}
push @Install_options, '-gcov'  if $Gcov;
push @Install_options, '-trick' if $Trick;

$JEOD_models = abs_path("$ENV{JEOD_HOME}/models");
$JEOD_libdir = "\${JEOD_HOME}/lib${Suffix}";
$JEOD_objdir = "obj${Suffix}";


die "Bad directory $Dir" unless (defined $Dir) && (-d $Dir) && ($Dir !~ m|/|);


parse_overrides();

get_directories();


$Is_modeldir = 1 if (scalar @Srcdirs) || (defined $Override_targets{compile});

create_makefile_header;
create_subdir_makefile_targets;

if ($Is_modeldir) {
   create_model_makefile_targets;
}

push @Text, @Final_overrides;

push @Text, "\n\n# Final targets generated by $script\n";
if (defined $Override_targets{CLEAN_OVERRIDES}) {
   push @Text, "\nclean:: \$(CLEAN_OVERRIDES)\n";
}
if (defined $Override_targets{REAL_CLEAN_OVERRIDES}) {
   push @Text, "\nreal_clean:: \$(REAL_CLEAN_OVERRIDES)\n";
}
push @Text, "\nreal_clean::\n";
if ($Top) {
   push @Text,
        "\t-rm -rf \$(JEOD_LIBDIR)\n",
        "\t-rm -f bin/jeod/defs.mk\n";
}
push @Text, "\t-rm -f \$(MAKEFILE) \$(MAKEFILE).bak \$(MAKEFILE).depends\n\n";

if ($Is_modeldir) {
   my $depend = '$(MAKEFILE).depends';
   push @Text, "\n\n",
               "ifeq ($depend,\$(wildcard $depend))\n",
               "include $depend\n",
               "endif\n";
}

update_file "$Cwd/$Dir/$Makefile", +(join '', @Text);

if ($Top) {
   my ($gcov_cflags, $config_cflags) = generate_cflags_options;
   update_file "bin/jeod/defs.mk",
      +(join "\n",
        "JEOD_MAKEFILE  := $Makefile",
        "JEOD_LIBDIR    := $JEOD_libdir",
        "ER7_UTILS_HOME := $ENV{ER7_UTILS_HOME}",
        "GCOV_CFLAGS    := $gcov_cflags",
        "COMMON_CFLAGS  := $ENV{TRICK_CFLAGS} -I\$(ER7_UTILS_HOME)",
        "CONFIG_CFLAGS  := $config_cflags",
        '');
}



################################################################################

sub get_directories() {
   my @contents;
   my $set_subdirs = (scalar (@Subdirs) == 0);

   if ($Reldir eq 'tools') {
      push @Subdirs, 'analysis'     if $Analysis;
      push @Subdirs, 'test_harness' if $Harness;
   }

   else {
      if (defined $Override_targets{SUBDIRS}) {
         my $in_subdirs = 0;
         die "SUBDIRS specified on command line and in jeod_makefile_overrides"
            if ! $set_subdirs;
         foreach my $line (@Initial_overrides) {
            if (! $in_subdirs) {
               if ($line =~ /^SUBDIRS *:?= *(.*)( *\\)?$/) {
                  my ($subdirs, $cont) = ($1, $2);
                  push @Subdirs, (split ' ', $subdirs);
                  $in_subdirs = 1;
                  last unless $cont;
               }
            } else {
               if ($line =~ /^ *(.*)( *\\)?/) {
                  my ($subdirs, $cont) = ($1, $2);
                  push @Subdirs, (split ' ', $subdirs);
                  last unless $cont;
               }
            }
         }
         $set_subdirs = 0;
      }

      opendir SUB, $Dir or die "Can't open directory $Dir";
      @contents = readdir SUB;
      closedir SUB;

      foreach my $ent (@contents) {
         if ((! -d "$Dir/$ent") ||
             ($ent =~ /^\./) ||
             ($ent =~ /^(verif|
                         include|
                         data|
                         docs|
                         io_src|
                         swig|
                         xml|
                         lib|
                         bin|
                         obj|
                         gcov|
                         deprecated|
                         auto_src|
                         SET_RUNS|
                         ascii|
                         ascii_full_set|
                         unit_test|
                         unit_tests|
                         a.out.dSYM)/x)) {
            next;
         }
         my @src = <$Dir/$ent/*.cc>;
         my @sub = <$Dir/$ent/*>;
         if (scalar @src) {
            push @Srcdirs, $ent;
         } elsif ($set_subdirs && scalar @sub) {
            push @Subdirs, $ent;
         }
      }
   }

   @Srcdirs = sort @Srcdirs;
   @Subdirs = sort @Subdirs;
}


sub parse_overrides() {
   my $makefile_overrides = "$Dir/jeod_makefile_overrides";

   if (-f $makefile_overrides) {
      my @ignore_header;
      my $section;

      open MAKEFILE_OVERRIDES, '<', $makefile_overrides
         or die "Can't open $makefile_overrides for input";

      $section = \@ignore_header;

      while (<MAKEFILE_OVERRIDES>) {
         if (/### INITIAL OVERRIDES ###/) {
            $section = \@Initial_overrides;
            $_ = "\n# Initial segment of $makefile_overrides\n";
         } elsif (/### FINAL OVERRIDES ###/) {
            $section = \@Final_overrides;
            $_ = "\n# Final segment of $makefile_overrides\n";
         }
         push @$section, $_;
      }
      close MAKEFILE_OVERRIDES;
   }


   if (scalar @Initial_overrides) {
      my @variables = qw (SUBDIRS
                          LIBNAME
                          COMPILE_OVERRIDES
                          CLEAN_OVERRIDES
                          REAL_CLEAN_OVERRIDES);
      foreach my $variable (@variables) {
         if (scalar (grep {/^${variable} *:?=/} @Initial_overrides)) {
            $Override_targets{$variable} = 1;
         }
      }
   }

   if (scalar @Final_overrides) {
      my @targets = qw (default all compile archive depend clean real_clean);
      foreach my $target (@targets) {
         if (scalar (grep {/^${target}:/} @Final_overrides)) {
            $Override_targets{$target} = 1;
         }
      }
   }
}


sub create_makefile_header() {
   my ($text);
   my ($gcov_cflags, $config_cflags) = generate_cflags_options;

   $text = <<"   EOF";
      ##########################################################################
      # Autogenerated makefile for $Cwd/$Dir
      ##########################################################################

      ######################
      # Non Parallel Mode. #
      ######################

      .NOTPARALLEL:

      SHELL = /bin/sh
      .SUFFIXES:
      .SUFFIXES: .cc .o

      .PHONY:
      .PHONY: default all compile archive update depend makefiles
      .PHONY: compile_msg archive_msg
      .PHONY: clean real_clean

      REL      := $Reldir
      MAKEFILE := $Makefile
      JMAKE    := \$(MAKE) -f \$(MAKEFILE)

      JEOD_BIN     := \$(JEOD_HOME)/bin/jeod
      JEOD_LIBDIR  := $JEOD_libdir
      JEOD_OBJDIR  := $JEOD_objdir
   EOF
   $text =~ s/^      //mg;
   $text =~ s/^   /\t/mg;

   push @Text, $text;

   if (scalar @Initial_overrides) {
      push @Text, @Initial_overrides;
   }

   $text = <<"   EOF";

      # Common configuration generated by $script

      INSTALL_MAKEFILE = perl \$(JEOD_BIN)/install_makefile.pl \\
                         @Install_options
      HIGHLIGHT        = perl \$(JEOD_BIN)/highlight_output.pl --
      HIGHLIGHT_NE     = perl \$(JEOD_BIN)/highlight_output.pl -q --
      GCOV_CFLAGS      = $gcov_cflags
      CONFIG_CFLAGS    = $config_cflags
      ER7_UTILS_HOME   = $ENV{ER7_UTILS_HOME}
      COMPILE_FLAGS    = \$(CONFIG_CFLAGS) \\
                         \$(CPP_PRE_DEF) \\
                         \$(TRICK_CFLAGS) \\
                         -I\$(ER7_UTILS_HOME) \\
                         \$(GCOV_CFLAGS) \\
                         \$(MODEL_COMPILE_FLAGS)
      COMPILER         = $Compiler
      COMPILE_CMD      = \$(COMPILER) \$(COMPILE_FLAGS)
      COMPILE          = \$(HIGHLIGHT) \$(COMPILE_CMD)
      DEPEND           = perl \$(JEOD_BIN)/update_dependencies.pl \\
                         \$(MAKEFILE).depends.temp

      export ER7_UTILS_HOME
   EOF
   $text =~ s/^      //mg;
   push @Text, $text, "\n";

   if (! defined $Override_targets{default}) {
      push @Text, "default: makefiles all\n";
   }
}


sub generate_cflags_options () {
   my $gcov_cflags = $Gcov ? '-fprofile-arcs -ftest-coverage' : '';
   my $config_cflags = '';
   if ($Trick) {
      my (@trick_ver, $trick_major, $trick_minor, $trick_source);
      @trick_ver = split /\./, $ENV{TRICK_VER};
      $trick_source = "\$(TRICK_HOME)/trick_source";
      $trick_major = $trick_ver[0];
      $trick_minor = $trick_ver[1];
      $config_cflags = join ' ',
                            "-DTRICK_VER=$trick_major",
                            "-DTRICK_MINOR=$trick_minor",
                            "-I$trick_source";
   }
   else {
      $config_cflags = '-DJEOD_UNIT_TEST';
   }
   return ($gcov_cflags, $config_cflags);
}


sub create_subdir_makefile_targets() {
   my ($text);
   my $trace = '--no-print-directory';
   ## $trace = '';

   if (scalar @Subdirs) {
      my $subdirs = join ' ', @Subdirs;
      push @Text, "\n# Subdirectory configuration generated by $script\n\n";

      if (! defined $Override_targets{SUBDIRS}) {
         push @Text, "SUBDIRS = $subdirs\n\n";
      }
      if ($Top) {
         $text = <<"         EOF";
            makefiles_msg:
               \@echo ""
               \@echo "\e[32m=== Creating makefiles ===\e[00m"
               \@echo ""

            makefiles:: makefiles_msg
         EOF
         $text =~ s/^            //mg;
         $text =~ s/^   /\t/mg;
         $text =~ s/\n$//;
         push @Text, $text, "\n";
      }
      else {
         push @Text, "makefiles::\n";
      }
      $text = <<"      EOF";
            \@for dir in \$(SUBDIRS); do \\
              if ! \$(INSTALL_MAKEFILE) "$Reldir" \$\$dir ; then \\
                echo "Install makefile in \$\$dir failed"; exit 1; \\
              fi ; \\
              if ! \$(JMAKE) -C \$\$dir $trace makefiles ; then \\
                echo "Make makefiles in \$\$dir failed"; exit 1; \\
              fi ; \\
            done
      EOF
      $text =~ s/^         //mg;
      $text =~ s/^   /\t/mg;
      $text =~ s/^\n//;
      push @Text, $text, "\n";

      if (! $Is_modeldir) {
         foreach my $target (qw(compile clean real_clean)) {
            my $override = uc ($target) . "_OVERRIDES";
            if (defined $Override_targets{$override}) {
               push @Text, "${target}:: \$($override)\n\n";
            }
         }
         if (defined $Override_targets{COMPILE_OVERRIDES}) {
            push @Text, "all:: \$(COMPILE_OVERRIDES)\n\n";
         }
      }

      foreach my $target (qw(all compile update depend clean real_clean)) {
         my @phony = map {$_ . "_$target"} @Subdirs;
         my $phony = join ' ', @phony;
         push @Text, ".PHONY: $phony\n${target}:: $phony\n\n";
         foreach my $subdir (@Subdirs) {
            push @Text, "${subdir}_${target}:\n",
                        "\t\@\$(JMAKE) -C $subdir $target\n\n";
         }
      }

   } else {
      my @targets = qw(makefiles);
      foreach my $target (qw(compile update depend clean)) {
         if ((! scalar @Srcdirs) &&
             (! defined $Override_targets{$target})) {
            push @targets, $target;
         }
      }
      if (scalar @targets) {
         push @Text, "\n# Null configuration generated by $script\n";
         foreach my $target (@targets) {
            push @Text, "${target}::\n\t\@true\n";
         }
      }
   }
}


sub create_model_makefile_targets() {
   my $text = '';
   my @install_targets =
      qw (all compile archive update depend depend_local clean real_clean);
   my %install_targets = ();
   my $vartext = '';
   my $cmdtext = '';
   my @srcsrc = map {'$(' . $_ . 'SRC)'} @Srcdirs;
   my @srcobj = map {'$(' . $_ . 'OBJ)'} @Srcdirs;
   my $srcsrc = join ' ', @srcsrc;
   my $srcobj = join ' ', @srcobj;
   my $srcdefs = '';
   my $names   = '';
   my $rules   = '';

   @install_targets{@install_targets} = (1) x @install_targets;

   foreach my $target (keys %Override_targets) {
      $install_targets{$target} = 0 if defined $install_targets{$target};
   }

   $text = "\n\n# Model configuration generated by $script\n\n";
   $vartext  = "OBJDIR       := \$(JEOD_OBJDIR)\n";
   if (! defined $Override_targets{LIBNAME}) {
      $vartext .= "LIBNAME      := jeod\n";
   }
   $vartext .= "JEOD_ARCHIVE := \$(JEOD_LIBDIR)/lib\$(LIBNAME).a\n";

   $cmdtext = <<"   EOF";
      \$(OBJDIR):
         mkdir \$(OBJDIR)

      \$(JEOD_LIBDIR):
         mkdir \$(JEOD_LIBDIR)

      compile_msg:
         \@echo ""
         \@echo "\e[32m=== Compiling \$(REL) source ===\e[00m"
         \@echo ""

      archive_msg:
         \@echo ""
         \@echo "\e[32m=== Archiving \$(REL) objects ===\e[00m"
         \@echo ""

      update_msg:
         \@echo ""
         \@echo "\e[32m=== Compile and archiving \$(REL) objects ===\e[00m"
         \@echo ""

   EOF
   $cmdtext =~ s/^      //mg;
   $cmdtext =~ s/^   /\t/mg;

   if ($install_targets{all}) {
      $cmdtext .= "all:: compile\n\n";
   }

   if ($install_targets{clean}) {
      $cmdtext .=
         "clean::\n\trm -rf \$(OBJ)\n\n";
   }

   if ($install_targets{real_clean}) {
      $cmdtext .=
         "real_clean::\n\trm -rf \$(OBJDIR)\n\n";
   }

   if ($install_targets{depend}) {
      $cmdtext .=
         "depend:: depend_local\n\n";
   }

   $text .= "$vartext\n$cmdtext";


   if ($install_targets{compile}) {
      my @compile_deps = qw($(OBJDIR) $(OBJ) archive);
      splice @compile_deps, 1, 0, '$(COMPILE_OVERRIDES)'
         if defined $Override_targets{COMPILE_OVERRIDES};
      my $deps = join ' ', 'compile_msg', @compile_deps;
      my $need_filter = 0;
      if (!$Trick && ($Reldir =~ /^models(\/|$)/) && (-d "$Dir/src")) {
         system "grep -q '^#ifdef TRICK_VER' $Dir/src/*.cc"
         or do {$need_filter = 1};
      }

      $text .=
         generate_rules
            'compile', $deps,
            sub($) {
               my $srcdir = shift;
               my $intro = '';
               my $srcfiles = "\$(wildcard $srcdir/*.cc)";
               if ($need_filter) {
                  $intro =
                     "# Filter out Trick-specific code in " .
                     "unit test environment\n" .
                     "${srcdir}TRK = " .
                     "\$(shell grep -l \"^\\#ifdef TRICK_VER\" $srcdir/*.cc)\n";
                  $srcfiles = "\$(filter-out \$(${srcdir}TRK),$srcfiles)";
               }
               $intro .
               "${srcdir}SRC = $srcfiles\n" .
               "${srcdir}OBJ = " .
                  "\$(patsubst %.cc,\$(OBJDIR)/%.o," .
                        "\$(notdir \$(${srcdir}SRC)))\n";
            },
            sub($) {
               my $srcdir = shift;
               my $extra = '$($*_CFLAGS)';
               "\$(${srcdir}OBJ): \$(OBJDIR)/\%.o : ${srcdir}/\%.cc\n" .
               "\t\@\$(COMPILE) $extra -c \$< -o \$@\n\n";

            },
            "SRC = $srcsrc", "OBJ = $srcobj";
   }

   if ($install_targets{archive}) {
      $cmdtext = <<"      EOF";

         archive:: archive_msg \$(JEOD_LIBDIR) \$(OBJ)
            ar -rv \$(JEOD_ARCHIVE) \$(OBJ)

      EOF
      $cmdtext =~ s/^         //mg;
      $cmdtext =~ s/^   /\t/mg;
      $text .= $cmdtext;
   }

   if ($install_targets{update}) {
      $cmdtext = <<"      EOF";

         ARC = \$(patsubst \%.o,\$(JEOD_ARCHIVE)(\%.o),\$(notdir \$(srcOBJ)))

         update:: update_msg \$(JEOD_LIBDIR) \$(ARC)

         \$(ARC): \$(JEOD_ARCHIVE)(\%.o): \$(OBJDIR)/\%.o
            ar rv \$(JEOD_ARCHIVE) \$(OBJDIR)/\$*.o

      EOF
      $cmdtext =~ s/^         //mg;
      $cmdtext =~ s/^   /\t/mg;
      $text .= $cmdtext;
   }

   if ($install_targets{depend_local}) {
      $cmdtext = <<"      EOF";
         depend_local:: depend_local_beg depend_local_src depend_local_end

         depend_local_beg:
            \@echo Making dependencies in $Reldir
            \@rm -f \$(MAKEFILE).depends.temp

         depend_local_end:
            \@\$(DEPEND) \$(MAKEFILE).depends.temp > \$(MAKEFILE).depends
            \@rm -f \$(MAKEFILE).depends.temp

      EOF
      $cmdtext =~ s/^         //mg;
      $cmdtext =~ s/^   /\t/mg;

      $cmdtext .=
         generate_rules
            'depend_local_src', '$(DEP)',
            sub($) {
               my $srcdir = shift;
               "${srcdir}DEP = " .
                  "\$(patsubst %.cc,\%.dummy_dep," .
                        "\$(notdir \$(${srcdir}SRC)))\n" .
               "DEP += \$(${srcdir}DEP)";
            },
            sub($) {
               my $srcdir = shift;
               my $extra = '$($*_CFLAGS)';
               "\$(${srcdir}DEP): \%.dummy_dep : ${srcdir}/\%.cc\n" .
               "\t\@\$(COMPILE_CMD) $extra -MM \$< >> " .
               "\$(MAKEFILE).depends.temp\n\n";
            };
      $text .= $cmdtext;
   }

   push @Text, $text;
}


sub generate_rules ($$$$;@) {
   my ($tgt, $deps, $name_gen, $rule_gen, @collect_names) = @_;
   my $names = '';
   my $rules = '';
   my $cmdtext = '';

   foreach my $srcdir (@Srcdirs) {
      $names .= &$name_gen ($srcdir);
      $rules .= &$rule_gen ($srcdir);
   }
   $names = join "\n", $names, @collect_names if scalar @collect_names;

   $cmdtext = <<"   EOF";
      __names_place_holder__

      ${tgt}:: $deps

      __rules_place_holder__

   EOF
   $cmdtext =~ s/^      //mg;
   $cmdtext =~ s/^   /\t/mg;
   $cmdtext =~ s/__names_place_holder__/$names/m;
   $cmdtext =~ s/__rules_place_holder__/$rules/m;

   return $cmdtext;
}


sub update_file($$) {
   my ($fname, $text) = @_;
   my $tmpfile = "$fname.tmp";
   my $bakfile = "$fname.bak";


   open  TEMP, '>', $tmpfile or die;
   print TEMP $text;
   close TEMP;

   if (-f $fname) {
      if (makefile_needs_update $tmpfile, $fname) {
         rename $fname, $bakfile or die "Can't rename $fname to $bakfile";
         rename $tmpfile, $fname or die "Can't rename $tmpfile to $fname";
         print "Updated $fname\n";
      } else {
         unlink $tmpfile;
      }
   } else {
      rename $tmpfile, $fname or die "Can't rename $tmpfile to $fname";
      print "Created $fname\n";
   }
}


sub makefile_needs_update($$) {
   my ($newfile, $oldfile) = @_;
   my ($newline, $oldline);
   my ($done, $needs_update);
   my $marker = "# DO NOT DELETE THIS LINE -- make depend depends on it.\n";

   open NEW, '<', $newfile or die;
   open OLD, '<', $oldfile or die;

   $done = $needs_update = 0;
   while (1) {
      $newline = <NEW>;
      $oldline = <OLD>;

      if (! defined $newline) {
         $needs_update = (defined $oldline) ? 1 : 0;
         $done = 1;
         last;
      }

      if ((! defined $oldline) || ($newline ne $oldline)) {
         $done = $needs_update = 1;
         last;
      }

      if ($newline eq $marker) {
         $done = 0;
         last;
      }
   }

   if (! $done) {
      $newline = <NEW>;
      $oldline = <OLD>;

      if (! defined $newline) {
         $needs_update = 0;
      } elsif ((! defined $oldline) || ($newline ne $oldline)) {
         $needs_update = 1;
      } else {
         while (1) {
            $newline = <NEW>;
            $oldline = <OLD>;

            if (! defined $newline) {
               $needs_update = (defined $oldline) ? 1 : 0;
               last;
            }

            if ((! defined $oldline) || ($newline ne $oldline)) {
               $needs_update = 1;
               last;
            }
         }
      }
   }

   return $needs_update;
}
