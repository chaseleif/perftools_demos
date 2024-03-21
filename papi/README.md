# PAPI - Performance API

### Source demonstrating functionality of PAPI

* `papi_instr.c` - Contains basic PAPI source code annotation using NATIVE counter names
  
___

### Steps to annotate source
* Initialize the PAPI library
* Create an event set
* Add events to the event set
  * Use the define for PRESET counters
  * or the string name of a NATIVE counter
* Start PAPI, this begins a region and activates counter collection
* Run some interesting code, functions, loops, etc
* Stop PAPI, this returns the counter values and implicitly sets counters to zero
* Use your counter values
* Cleanup the event set
* Destroy the event set
___

#### Papi Utilities

Applications from the 6.0.0.1 install:
```bash
/usr/bin/papi_avail
/usr/bin/papi_clockres
/usr/bin/papi_command_line
/usr/bin/papi_component_avail
/usr/bin/papi_cost
/usr/bin/papi_decode
/usr/bin/papi_error_codes
/usr/bin/papi_event_chooser
/usr/bin/papi_hl_output_writer.py
/usr/bin/papi_mem_info
/usr/bin/papi_multiplex_cost
/usr/bin/papi_native_avail
/usr/bin/papi_version
/usr/bin/papi_xml_event_info
```

The `papi{,component,native}_avail` commands will show available counters.

Counters can be disabled in a system depending on `/proc/sys/kernel/perf_event_paranoid`[^1]

[^1]: See the script in the perf folder, `$ ../perf/paranoia.sh` for more information.
___

#### Resources
  
[PAPI Home Page](https://perf.wiki.kernel.org/index.php/Tutorial)  

[PAPI(3) at die.net](https://linux.die.net/man/3/papi)  
[PAPI_perror and PAPI_strerror](https://linux.die.net/man/3/papi_strerror)  
[PAPI_library_init and PAPI_is_initialized](https://linux.die.net/man/3/papi_library_init)  
[PAPI_create_eventset](https://linux.die.net/man/3/papi_create_eventset)  
[PAPI_event_name_to_code and PAPI_event_code_to_name](https://linux.die.net/man/3/papi_event_code_to_name)  
[PAPI_add_events](https://linux.die.net/man/3/papi_add_events)  
[PAPI_start and PAPI_stop](https://linux.die.net/man/3/papi_start)  
[PAPI_cleanup_eventset and PAPI_destroy_eventset](https://linux.die.net/man/3/papi_cleanup_eventset)  
[PAPI_shutdown](https://linux.die.net/man/3/papi_shutdown)  
___
