vehicle.trans_init.dyn_subject              = vehicle.dyn_body
vehicle.trans_init.reference_ref_frame_name = "Space.inertial"
vehicle.trans_init.body_frame_id            = "composite_body"
vehicle.trans_init.position                 = [0.0 , 0.0 , 0.0]
vehicle.trans_init.velocity                 = [0.0 , 0.0 , 0.0]


vehicle.rot_init.dyn_subject              =  vehicle.dyn_body
vehicle.rot_init.reference_ref_frame_name = "Space.inertial"
vehicle.rot_init.body_frame_id            = "composite_body"
vehicle.rot_init.orientation.data_source  = trick.Orientation.InputEigenRotation
vehicle.rot_init.orientation.eigen_angle  = 0.0
vehicle.rot_init.orientation.eigen_axis   = [0, 0, 1] 
vehicle.rot_init.ang_velocity             = [0.0, 0.0, 0.0]

dynamics.dyn_manager.add_body_action( vehicle.trans_init )
dynamics.dyn_manager.add_body_action( vehicle.rot_init )
