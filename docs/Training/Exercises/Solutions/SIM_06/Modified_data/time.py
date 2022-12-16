# Initialize with UTC calendar date.
jeod_time.time_manager_init.initializer = "UTC"
jeod_time.time_manager_init.sim_start_format = trick.TimeEnum.calendar

# Time initialization data.
# Midnight on March 10 2003.
jeod_time.time_utc.calendar_year   = 2003
jeod_time.time_utc.calendar_month  =    4
jeod_time.time_utc.calendar_day    =   10
jeod_time.time_utc.calendar_hour   =    0
jeod_time.time_utc.calendar_minute =    0
jeod_time.time_utc.calendar_second =  0.0

jeod_time.time_tai.initialize_from_name = "UTC"
jeod_time.time_tai.update_from_name = "Dyn"
jeod_time.time_utc.update_from_name = "TAI"
