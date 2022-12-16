################TRICK HEADER#######################################
#PURPOSE:
#  (To define the method set_ISS_trans_Orbit_inertial_body_set02
####################################################################################

#Auto-generated from the data file with this header:
#/*******************************************************************************
#
#Purpose:
#  (Specify ISS orbit, J2000 reference, set #02,
#   at STS_114 MET 001:19:30:59.000.
#   Data based on state vectors from
#   The Flight Operations Directorate, NASA JSC )
#
#
#
#*******************************************************************************/

def set_ISS_trans_Orbit_inertial_body_set02(vehicle_reference, dynamics) :




  vehicle_reference.orb_init.dyn_subject = vehicle_reference.dyn_body
  vehicle_reference.orb_init.action_name = "ISS>trans_Orbit_inertial_body_set02"

  vehicle_reference.orb_init.reference_ref_frame_name = "Earth.inertial"
  vehicle_reference.orb_init.body_frame_id = "composite_body"

  vehicle_reference.orb_init.set              = 2
  vehicle_reference.orb_init.orbit_frame_name = "Earth.inertial"
  vehicle_reference.orb_init.planet_name      = "Earth"

  vehicle_reference.orb_init.arg_periapsis  = trick.attach_units( "degree",100.582445989)
  vehicle_reference.orb_init.eccentricity            =    0.00129073350
  vehicle_reference.orb_init.inclination  = trick.attach_units( "degree",51.670450765)
  vehicle_reference.orb_init.ascending_node  = trick.attach_units( "degree",49.708417385)
  vehicle_reference.orb_init.mean_anomaly  = trick.attach_units( "degree",300.012677353)
  vehicle_reference.orb_init.semi_major_axis  = trick.attach_units( "km",6732.90120152)



  dynamics.dyn_manager.add_body_action (vehicle_reference.orb_init)

  #undef VEHICLE.orb_init

  return
