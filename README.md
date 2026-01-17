Rosalinde (legacy C/Tcl/Tk RPC system)
=====================================

Overview
--------
Rosalinde is a legacy client-server application originally developed in the mid-1990s. It uses ONC/Sun RPC for inter-process communication, plain C for most server components, and a Tcl/Tk-based GUI client.

This repository contains the original source tree with minimal portability fixes applied to compile and run on modern Linux systems (glibc, libtirpc, Tcl/Tk 8.6).

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
Rosalinde uses an RPC broker and several RPC services. To run the system locally, follow this order:

1. Start the system RPC portmapper (rpcbind):

```bash
sudo systemctl start rpcbind
# or: sudo service rpcbind start
```

2. Start the broker service (from `exe/` or `src/rosa`):

```bash
./exe/r_brok_svc &
```

3. Start the table services that the account services depend on:

```bash
./exe/r_btab_knde_svc localhost &
./exe/r_btab_knto_svc localhost &
```

4. Start the account services:

```bash
./exe/r_knto_svc localhost &
./exe/r_knde_svc localhost &
```

5. Start the GUI client pointing to the broker host (usually `localhost`):

```bash
# from repository root
./src/rosa/rosa_local src/rosa/rosa.tk localhost &
```

Notes about service order: `r_btab_knde_svc` and `r_btab_knto_svc` must be running before `r_knto_svc` and `r_knde_svc` to avoid RPC transport errors seen in testing.

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
- The GUI expects dialog definitions (`*.dlg`) and `tools.tcl` in `src/rosa`. At startup the application generates/uses `tclIndex` to autoload dialog procedures.
- To run the GUI locally provide the Tcl script and the broker host as arguments (see example above).

Patches and compatibility changes made
-------------------------------------
This port included small, focused compatibility patches such as:
- Add `-ltirpc` to link flags and set `TCL_LIBS` to `-ltk8.6 -ltcl8.6` in `make/env.mak`.
- Provide handwritten XDR sources for a few RPC types that `rpcgen` could not generate with modern rpcgen.
- Fix Tcl/Tk API usage (e.g., `Tcl_SetVar` used instead of assigning `tcl_RcFileName`, create dialog command names correctly).
- Tweak `src/rosa/rosa.tk` to source `tclIndex` robustly and avoid `glob` errors on modern Tcl.

Where to go from here
----------------------
- Generate a full changelog from git/diffs (optional).
- Run the GUI interactively to test workflows.
- If packaging, consider creating a small systemd unit for the broker and services.

License and credits
-------------------
This is a port of legacy code from 1996. Original authors credited in source headers. Use and distribution depend on the original license notices included in the sources.


