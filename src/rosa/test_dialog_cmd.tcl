#!/usr/bin/env tclsh

# Test ob dialog command jetzt geladen wird
set dir .
source tclIndex

if {[info exists auto_index(dialog)]} {
    puts "✓ dialog in auto_index gefunden"
    eval $auto_index(dialog)
    if {[llength [info commands dialog]] > 0} {
        puts "✓ dialog Befehl geladen"
    }
} else {
    puts "✗ dialog NOT in auto_index"
}
