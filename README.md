Rosalinde (legacy C/Tcl/Tk RPC system)
=====================================

Overview
--------
Rosalinde is a pioneering microservices-based client-server application originally developed at Fachhochschule Rosenheim in 1996. It demonstrates an early and sophisticated approach to distributed systems architecture, predating modern microservices by over a decade.

The system uses ONC/Sun RPC for inter-process communication, plain C for server components, and a Tcl/Tk-based GUI client. It was designed as a modular, service-oriented system that can be deployed as either separate microservices or combined into a monolithic build for debugging and local development.

This repository contains the original source tree with minimal portability fixes applied to compile and run on modern Linux systems (glibc, libtirpc, Tcl/Tk 8.6).

## System Architecture

### Core Concept: Customer and Account Management Services

Rosalinde implements a two-tier service architecture with independent data services:

**Customer Service (Kundenservice / knde):**
- Manages customer information (Anrede, Vorname, Name, Strasse, PLZ, Ort, Land, etc.)
- Separate RPC service (`r_knde_svc`) that handles customer entity operations
- Maintains relationships with accounts
- Communicates through dedicated RPC interface

**Account Service (Kontendienst / knto):**
- Manages bank account information (Konto-Nr, BLZ, Bank, etc.)
- Separate RPC service (`r_knto_svc`) that handles account entity operations
- Links to customers through account selection
- Independent data management via dedicated RPC interface

**Database Services (Btab layer):**
- Each data service (customer, account) has a dedicated persistence layer
  - `r_btab_knde_svc` — database service for customer entities
  - `r_btab_knto_svc` — database service for account entities
- These services abstract all database access, implementing the "Data Access Object" pattern
- Data is serialized and stored in local `.DAT` files (e.g., `KNDE.DAT`)
- This design allows each service to be independently deployed with its own data storage

**RPC Broker:**
- Central registry service (`r_brok_svc`) that coordinates service discovery
- Enables loose coupling between client and servers
- Services register themselves; clients query the broker to locate services

### Data Flow

```
GUI Client (rosa_local/rosa_rpc)
    ↓
    ├→ [Query Broker] → Find customer/account services
    ↓
    ├→ Customer Service (r_knde_svc)
    │     ↓
    │     └→ Customer DB Service (r_btab_knde_svc) → KNDE.DAT
    ↓
    └→ Account Service (r_knto_svc)
          ↓
          └→ Account DB Service (r_btab_knto_svc) → (account data)
```

### Service Modularity

The system's architecture enables three deployment modes:

1. **Monolithic (LOCAL mode):** All services run in-process with the GUI. Used for development and debugging. Compiled with `-DLOCAL`.

2. **Distributed (RPC mode):** Each service runs as a separate process. Services communicate via RPC. The GUI uses RPC client stubs to interact with remote services. Compiled without `-DLOCAL`, linked against RPC client libraries.

3. **Hybrid:** The broker and some core services can run on separate machines, while the GUI and local data services run co-located. This flexibility was ideal for 1990s system designs.

### GUI Architecture

The Tcl/Tk GUI (`rosa_local`, `rosa_rpc`) provides:
- **Menu-based navigation** — Stammdaten (master data), Administration, Help
- **Dialog-driven workflows** — Modal dialogs for customer maintenance, account selection, server administration
- **Dynamic dialog loading** — Tcl procedures are autoloaded on demand from `.dlg` files
- **Utility procedures** — Shared dialog infrastructure (`tools.tcl` provides the `dialog` command)
- **RPC integration** — The `tcl_dlg.c` module bridges Tcl and C, enabling GUI callbacks to invoke C functions

### Abstract Data Types (ADT)

The `src/adt/` directory contains abstract data type implementations:
- `knde/` — Customer entity type and operations
- `knto/` — Account entity type and operations
- Each ADT has both local (in-process) and remote (RPC client) variants
- This allows the same business logic to work in both monolithic and distributed deployments

### Build Architecture

The `make/` directory contains modular makefile fragments:
- `env.mak` — environment variables, compiler flags, library paths
- `lib.mak` — rules for building shared libraries
- Individual `.mak` files for test targets (e.g., `tt_knde.mak`)
- The top-level `Makefile` orchestrates the entire build

This modular make system allows:
- Selective builds (e.g., rebuild only customer services)
- Clear dependency tracking
- Support for both debug and release builds
- Easy addition of new services or test clients

Repository layout
-----------------
- `src/` — main source tree
  - `rosa/` — Tcl/Tk GUI, dialogs, and GUI entrypoint `rosa_local` and `rosa_rpc`
  - `adt/`, `btab/`, `knde/`, `knto/` — application logic, RPC servers and clients
  - `tk/` — Tcl/Tk glue (`tcl_dlg.c`) and helpers
  - `util/` — utility modules
- `make/` — top-level make fragments and build rules
- `include/` — public headers
- `exe/` — (after build) runtime binaries
- `lib/` — (after build) built libraries
- `doc/` — assorted documentation and configuration templates

Build requirements
------------------
- A POSIX-compatible Linux system
- `gcc` (modern version, e.g. 9+)
- GNU `make`
- `libtirpc` and development headers (for ONC RPC compatibility)
- Tcl/Tk 8.6 development packages (headers and libraries)
- Standard Unix build tools: `autoconf` not required; the project uses hand-written makefiles

On Debian/Ubuntu you can install needed packages with:

```bash
sudo apt update
sudo apt install build-essential libtirpc-dev libtk8.6-dev libtcl8.6-dev rpcbind
```

Build instructions
------------------
From the repository root run:

```bash
# perform a full build
make -C make all
```

This will compile libraries and produce executables in `exe/` and object/library files in `lib/`.

If you only want the GUI client, build the `rosa_local` target:

```bash
make -C src/rosa rosa_local
```

Runtime: services and order
---------------------------

Rosalinde can be run in two modes:

### Local (Monolithic) Mode
All services run in-process within the GUI application. This is ideal for development and debugging:

```bash
./src/rosa/rosa_local localhost localhost
```

### Distributed (RPC) Mode
Services run as separate processes and communicate via RPC:

```bash
# 1. Start the system RPC portmapper (rpcbind):
sudo systemctl start rpcbind

# 2. Start the broker service
./exe/r_brok_svc &

# 3. Start the database/persistence services (must start before business logic services)
./exe/r_btab_knde_svc localhost &
./exe/r_btab_knto_svc localhost &

# 4. Start the business logic services
./exe/r_knto_svc localhost &
./exe/r_knde_svc localhost &

# 5. Start the GUI client (pointing to broker host)
./src/rosa/rosa_rpc localhost localhost &
```

**Important:** Service startup order matters. The table/persistence services (`r_btab_knde_svc`, `r_btab_knto_svc`) must be running before the business logic services (`r_knto_svc`, `r_knde_svc`). This ensures that when business logic services start and try to register or communicate with persistence services, those services are already available.

### Using the Startup Script

Alternatively, use the provided startup script from the `bin/` directory:

```bash
cd bin/
./Rosalinde
```

The script will:
1. Prompt for the broker host
2. Start all RPC services in order
3. Launch the GUI client
4. Display a summary

Tests and debugging
-------------------
A set of simple test clients exist in `exe/`, for example `tt_r_knto` and `tt_r_knde`. Run them against `localhost` once services are up:

```bash
./exe/tt_r_knto localhost
./exe/tt_r_knde localhost 1
```

If you encounter RPC transport errors, ensure `rpcbind` is running, the broker is registered, and service startup order is correct. Use `rpcinfo -p` to verify registered services.

Tcl/Tk GUI notes
----------------

The GUI implementation demonstrates sophisticated 1990s UI programming patterns:

**Dialog System:**
- Dialog definitions stored in `.dlg` files (e.g., `dlg_copy.dlg`, `dlg_abou.dlg`)
- Each dialog file contains a Tcl procedure that builds and displays the dialog
- The `tools.tcl` module provides the base `dialog` command for consistent dialog styling
- Dialogs are loaded on-demand using Tcl's autoload mechanism (via `tclIndex`)

**Startup Sequence:**
1. The application loads `rosa.tk` (or `rosa.tk_script` for alternative mode)
2. `rosa.tk` sources `tools.tcl` explicitly to provide the base `dialog` command
3. Tcl's `auto_mkindex` is run to generate `tclIndex`, which catalogs all dialog procedures for lazy loading
4. The main window is created with a menu bar
5. Dialogs are loaded and executed on demand when menu items are selected

**Menu Structure:**
- **Stammdaten (Master Data)** — Pflege Kunden (Customer Maintenance), Pflege Konten (Account Maintenance)
- **Administration** — Server Administration, Broker Selection
- **About** — Copyright, System Information

**GUI-to-Service Communication:**
- The `tcl_dlg.c` module implements Tcl commands that bridge the GUI to C business logic
- In local mode, these commands directly invoke in-process C functions
- In RPC mode, they invoke RPC client stubs that communicate with remote services

### Font and Layout Fixes

The original system used X11 font specifications (`-Adobe-Times-Medium-R-Normal-*-140-*`) which are not reliably available on modern systems. The port fixes this by using portable Tcl/Tk font specifications (`{Times 10}`), ensuring consistent rendering across different Linux distributions.

Patches and compatibility changes made
-------------------------------------

This port included targeted compatibility patches to modernize the system for current Linux distributions:

**RPC and Build System:**
- Add `-ltirpc` to link flags and set `TCL_LIBS` to `-ltk8.6 -ltcl8.6` in `make/env.mak`.
- Provide handwritten XDR sources for a few RPC types that `rpcgen` could not generate with modern rpcgen.

**Tcl/Tk API and GUI:**
- Fix Tcl/Tk API usage (e.g., `Tcl_SetVar` and proper variable handling)
- Correct command-line argument handling in `src/rosa/rosa.c` to properly pass the startup script to `Tk_Main`
- Explicit `source tools.tcl` in `rosa.tk` and `rosa_rpc.tk` to ensure the base `dialog` command is always available before `auto_mkindex` runs
- Use portable Tcl/Tk font specifications (`{Times 10}`) instead of X11 font strings
- Adjust dialog message widget width and font size for proper rendering on modern displays

**tclIndex Generation:**
- Modernize `tclIndex` to use `[file join $dir ...]` instead of string concatenation (`$dir/...`)
- This ensures correct path resolution across different deployment scenarios

### Key Insights from This Port

This system was remarkably ahead of its time:

1. **Service-Oriented Architecture** — 1996 implementation of microservices, long before the term existed in its modern context.

2. **Loose Coupling** — Services communicate through a broker, allowing independent development, testing, and deployment.

3. **Flexible Deployment** — The same codebase can run in monolithic or distributed modes without changes. This was essential for 1990s system development when testing distributed systems was difficult.

4. **Clear Separation of Concerns** — Data services (Btab), business logic services (Knde, Knto), and the GUI are completely separated.

5. **Portable Build System** — Hand-written makefiles that cleanly separate build rules, making it easy to understand and modify.

Where to go from here
----------------------

- **Experiment with service deployment:** Try running different combinations of services (local, RPC, hybrid) to understand the flexibility of the architecture.
- **Study the RPC interfaces:** The `.x` files define the RPC contracts between services. These are excellent examples of distributed system design.
- **Extend the system:** The modular structure makes it easy to add new services (e.g., a transaction service) following the same patterns.
- **Run the GUI interactively:** Use the customer and account maintenance dialogs to understand the user workflows.
- **Trace RPC calls:** Use tools like `strace` to observe how services communicate via RPC.
- **Review the build system:** The makefiles demonstrate clear, maintainable build organization without autotools.

### Educational Value

Rosalinde is an excellent case study for:
- Service-oriented and distributed systems architecture
- RPC-based inter-process communication (ONC RPC / Sun RPC)
- C/Tcl integration and GUI programming in the 1990s
- Data abstraction and layering patterns
- Build system design for modular projects
- Backward compatibility and portability across decades of Unix/Linux evolution

License and credits
-------------------

**Original Development:**
- Concept and Design: Prof. Dr. Johannes Siedersleben
- Implementation: Johannes Weigend, Christian Stoellinger
- Fachhochschule Rosenheim, Anwendungsentwicklung (Distributed Systems)
- Developed: March–July 1996

**Modern Port (2026):**
- Portability fixes and modernization for Linux/Tcl 8.6
- Minimal changes to preserve original architecture and intent

Use and distribution depend on the original license notices included in the source files. This port is provided for educational and historical purposes.

---

**Last Updated:** January 2026  
**Status:** Fully functional, tested on modern Linux distributions


