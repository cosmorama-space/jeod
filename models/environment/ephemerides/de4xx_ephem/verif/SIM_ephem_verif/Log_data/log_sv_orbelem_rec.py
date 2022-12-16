#Auto-generated from the data file with this header:
#/*
#PURPOSE:
#    (Log data for orbital vehicle orbital elements data.)
#
#REFERENCES:
#    (None)
#
#ASSUMPTIONS AND LIMITATIONS:
#    (none)
#
#
#*/

def log_sv_orbelem_rec ( log_cycle , VEH_NAME , VEH_OBJ ) :
  recording_group_name =  ""+VEH_NAME+"_Orb_Elem"
  dr_group = trick.sim_services.DRBinary(recording_group_name)
  dr_group.thisown = 0
  dr_group.set_cycle(log_cycle)
  dr_group.freq = trick.sim_services.DR_Always
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.semi_major_axis")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.semiparam")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.e_mag")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.inclination")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.arg_periapsis")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.long_asc_node")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.r_mag")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.vel_mag")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.true_anom")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.mean_motion")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.orbital_anom")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.orb_energy")
  dr_group.add_variable(   ""+VEH_OBJ+".orb_elem.elements.orb_ang_momentum")

  trick.add_data_record_group(dr_group)
  return
