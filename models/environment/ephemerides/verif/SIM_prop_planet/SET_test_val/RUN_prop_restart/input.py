################################################################################
# PURPOSE:
#   (To define the input data for simulation run SET_test/RUN_prop_restart/)
################################################################################


# Import the JEOD checkpoint/restart module.
import sys
import os
sys.path.append ('/'.join([os.getenv("JEOD_HOME"), "lib/jeod/python"]))
import jeod_checkpoint_restart

# Set up the simulation.
# The default setup uses the ephemeris model to set translational state.
LOG_CYCLE = 60*86400
exec(compile(open("Modified_data/setup.py", "rb").read(), "Modified_data/setup.py", 'exec'))
set_setup()

# Set planet rotations to zero.
jupiter.rot_init.ang_velocity[2] = trick.attach_units("rad/s", 0.0)
saturn.rot_init.ang_velocity[2] = trick.attach_units("rad/s", 0.0)
sun.rot_init.ang_velocity[2] = trick.attach_units("rad/s", 0.0)

# Use a bogus integrator.
integ_constructor.switch_integ_to_Euler()

# Safety: set the sim to run for 60 days.
# The restart should override this.
trick.stop(60*86400)

# Restart the sim from the checkpoint data in SET_test/RUN_prop_checkpoint.
jeod_checkpoint_restart.restore_from_checkpoint (
  "SET_test/RUN_prop_checkpoint", "chkpnt_5184000.000000")
