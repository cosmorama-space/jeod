exec(compile(open("SET_test/input_core.py", "rb").read(), "SET_test/input_core.py", 'exec'))

vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
vehicle.pos.ellip_coords.longitude = set_units("degree", 110.0)

trick.add_read(1, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -180.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(2, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -170.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(3, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -160.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(4, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -150.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(5, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -140.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(6, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -130.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(7, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -120.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(8, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -110.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(9, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -100.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(10, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -90.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(11, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -80.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(12, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -70.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(13, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -60.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(14, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -50.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(15, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -40.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(16, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -30.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(17, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -20.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(18, """
vehicle.pos.ellip_coords.longitude = set_units("degree", -10.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(19, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 00.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(20, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 10.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(21, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 20.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(22, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 30.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(23, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 40.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(24, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 50.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(25, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 60.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(26, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 70.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(27, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 80.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(28, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 90.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(29, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 100.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(30, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 110.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(31, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 120.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(32, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 130.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(33, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 140.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(34, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 150.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(35, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 160.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.add_read(36, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 170.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 649.9999)
""")

trick.add_read(37, """
vehicle.pos.ellip_coords.longitude = set_units("degree", 180.00)
vehicle.pos.ellip_coords.altitude = set_units("km", 650.0)
""")

trick.exec_set_terminate_time(38)
