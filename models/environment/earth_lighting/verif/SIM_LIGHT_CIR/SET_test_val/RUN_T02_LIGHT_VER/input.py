# This is an input file for the lighting verification
#
# Scott Piggott
# July 2006
#

exec(compile(open("Modified_data/default_mods.py", "rb").read(), "Modified_data/default_mods.py", 'exec'))

mngr.sun.inertial.state.trans.position  = [1, 1.5, 0.0]
mngr.moon.inertial.state.trans.position = [1, 0.0, 0.0]

light.lighting.sun_earth.phase = 1
light.lighting.moon_earth.phase = 1
light.lighting.earth_albedo.phase = 1

trick.add_read(1.0, """
light.r_bottom  = 3.0
light.r_top     = 3.0
light.d_centers = 1.0
""")
