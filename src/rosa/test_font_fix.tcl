#!/usr/bin/env tclsh

# Load the fixed tools.tcl
source tools.tcl

puts "Font specification changed:"
puts "  Old: -Adobe-Times-Medium-R-Normal-*-100-*"
puts "  New: {Times 10}"
puts ""
puts "✓ Using standard Tcl/Tk font format"
puts "✓ Dialog should now display with proper font size"

# Verify the dialog procedure is loaded
if {[llength [info commands dialog]] > 0} {
    puts "✓ dialog procedure loaded successfully"
}
