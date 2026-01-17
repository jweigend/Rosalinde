#!/usr/bin/env tclsh
package require Tk

# Check available fonts
puts "Available fonts:"
foreach font [lsort [font families]] {
    puts "  $font"
}

puts ""
puts "Standard fonts:"
puts "  Times: [font configure TkDefaultFont]"

# Create test fonts
catch {font configure testfont} err
puts ""
puts "Font configuration test:"
catch {font create testfont -family "Times" -size 10} result
puts "  Created: $result"
