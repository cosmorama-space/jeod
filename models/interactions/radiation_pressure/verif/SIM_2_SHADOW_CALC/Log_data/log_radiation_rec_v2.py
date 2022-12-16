#Auto-generated from the data file with this header:
#/*
#PURPOSE:
#    (Log data for radiation testing.)
#
#REFERENCES:
#    (None)
#
#ASSUMPTIONS AND LIMITATIONS:
#    (none)
#
#
#*/

def log_radiation_rec_v2 ( log_cycle ) :
  recording_group_name =  "radiation_profile"
  dr_group = trick.sim_services.DRBinary(recording_group_name)
  dr_group.thisown = 0
  dr_group.set_cycle(log_cycle)
  dr_group.freq = trick.sim_services.DR_Always

  dr_group.add_variable(   "radiation.rad_pressure.source.flux_mag")
  for ii in range(0,3) :
    dr_group.add_variable("vehicle.dyn_body.structure.state.trans.position[" + str(ii) + "]" )
    dr_group.add_variable("radiation.rad_pressure.force[" + str(ii) + "]" )
    dr_group.add_variable("radiation.rad_pressure.torque[" + str(ii) + "]" )
    dr_group.add_variable("radiation.rad_surface.force[" + str(ii) + "]" )
    for jj in range(0,10) :
      dr_group.add_variable("radiation.data_rec.F_absorption[" + str(jj) + "][" + str(ii) + "]" )
      dr_group.add_variable("radiation.data_rec.F_diffuse[" + str(jj) + "][" + str(ii) + "]" )
      dr_group.add_variable("radiation.data_rec.F_emission[" + str(jj) + "][" + str(ii) + "]" )
      dr_group.add_variable("radiation.data_rec.F_specular[" + str(jj) + "][" + str(ii) + "]" )
      dr_group.add_variable("radiation.data_rec.force[" + str(jj) + "][" + str(ii) + "]" )
      dr_group.add_variable("radiation.data_rec.torque[" + str(jj) + "][" + str(ii) + "]" )
  for ii in range(0,10) :
    dr_group.add_variable("radiation.data_rec.temperature[" + str(ii) + "]" )
    dr_group.add_variable("radiation.data_rec.power_absorb[" + str(ii) + "]" )
    dr_group.add_variable("radiation.data_rec.power_emit[" + str(ii) + "]" )

  trick.add_data_record_group(dr_group)
  return
