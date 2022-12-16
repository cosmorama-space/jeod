# Rerun RUN_01, adjusting values
exec(compile(open("Modified_data/system.py", "rb").read(), "Modified_data/system.py", 'exec'))

parent_mass_default()
parent_mass_inertia_optionB()

child1_mass_default()
child1_mass_inertia_optionA()

attach1_default()
components.attach1.offset_pstr_cstr_pstr  = [ 0.0, 0.0, 2.0]

components.file_name = "SET_test/RUN_06/mass.out"
