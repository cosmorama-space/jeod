################TRICK HEADER#######################################
#PURPOSE:
#  (To define the elements to be logged in the logging of rec) 
####################################################################################

def log_state ( log_cycle ) :
  recording_group_name = "state" 
  dr_group = trick.sim_services.DRBinary(recording_group_name)
  dr_group.thisown = 0
  dr_group.set_cycle(log_cycle)
  dr_group.freq = trick.sim_services.DR_Always
  for ii in range(0,3) :
    dr_group.add_variable( "vehicle.vehicle_plate.normal[" + str(ii) +"]")
    dr_group.add_variable( "vehicle.array_plate.normal[" + str(ii) +"]")
    dr_group.add_variable( "vehicle.vehicle_plate.position[" + str(ii) +"]")
    dr_group.add_variable( "vehicle.array_plate.position[" + str(ii) +"]")
    dr_group.add_variable( "interactions.rad_pressure.force[" + str(ii) +"]")


  trick.add_data_record_group(dr_group)

  return
