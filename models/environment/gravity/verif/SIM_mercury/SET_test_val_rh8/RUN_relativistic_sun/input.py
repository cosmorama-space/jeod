import Modified_data

Modified_data.configure_trick(trick, trick_sys)
Modified_data.configure_time(trick, jeod_time, base="TDB")
Modified_data.configure_env(env)
Modified_data.configure_gravity(trick,
    sun, venus, earth, moon, mars, jupiter, saturn, uranus, neptune)
Modified_data.configure_mercury(trick, dynamics, mercury, set(range(1)))

Modified_data.log_arg_peri(131072.0)

trick.add_read(0 , """
mercury.prop_planet.commanded_mode = \
    trick.PropagatedPlanet.TransFromBody_RotFromBody
""")

integ_constructor.constructor = integ_constructor.gj_constructor
integ_loop.integ_loop.set_deriv_ephem_update (True)
