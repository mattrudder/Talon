
#pragma once

/** Defines whether or not we're compiling with PhysX support. */
//#define TALON_PHYSX_SUPPORT

/** Defines whether or not assertions should stop the current application. */
#define TALON_ASSERTS_ENABLED

/** Defines whether or not the PhysX Visual Remote Debugger should be enabled. */
#define TALON_ENABLE_PHYSX_VRD

/** Defines the build as supporting PerfHUD. Uncomment the line below if you wish to compile with PerfHUD support. */
#define TALON_SUPPORT_PERFHUD

/** Defines a logger interface for outputting log info to the console. */
#define TALON_CONSOLE_LOGGING

/** With this flag required, malloc and global new are disabled. Requires all systems to use engine based memory management. */
//#define TALON_ALLOCATORS_ONLY