#!/usr/bin/env tclsh

# Simuliere rosa.tk Startup
if {[llength [glob -nocomplain *.tcl]]} {
  auto_mkindex . *.tcl
}
if {[llength [glob -nocomplain *.dlg]]} {
  auto_mkindex . *.dlg
}

# Load tools.tcl explicitly
source tools.tcl

set auto_path \
  [linsert $auto_path 0 .]
if {[file exists tclIndex]} {
  set dir .
  source tclIndex
}

# Now test if dialog is available
if {[llength [info commands dialog]] > 0} {
    puts "✓ dialog command is available"
} else {
    puts "✗ dialog command NOT available"
}

# Test if DLG_CopyRight can be called
if {[info exists auto_index(DLG_CopyRight)]} {
    puts "✓ DLG_CopyRight in auto_index"
    eval $auto_index(DLG_CopyRight)
    if {[llength [info commands DLG_CopyRight]] > 0} {
        puts "✓ DLG_CopyRight procedure loaded"
    }
}
