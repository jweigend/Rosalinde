#!/usr/bin/env tclsh

# Laden der tclIndex für Dialog-Autoload
set dir .
if {[file exists tclIndex]} {
    source tclIndex
}

# Test: Versuche, jede Dialog-Prozedur zu laden
set dialogs {
    DLG_AboutAE10
    DLG_CopyRight
    DLG_Pflege_Konten
    DLG_Pflege_Kunden
    DLG_ServerAdmin
    DLG_SelectBroker
    DLG_Suche_Konto
    dialog
}

set success 0
set failed 0

foreach dlg_name $dialogs {
    if {[catch {
        # Versuche, die Prozedur zu laden (autoload)
        if {[info exists auto_index($dlg_name)]} {
            eval $auto_index($dlg_name)
            if {[llength [info commands $dlg_name]] > 0} {
                puts "✓ Dialog geladen: $dlg_name"
                incr success
            } else {
                puts "✗ Dialog NICHT geladen: $dlg_name"
                incr failed
            }
        } else {
            puts "✗ Dialog nicht in auto_index: $dlg_name"
            incr failed
        }
    } err]} {
        puts "✗ Fehler beim Laden von $dlg_name: $err"
        incr failed
    }
}

puts "\n========== ERGEBNIS =========="
puts "Erfolgreich geladen: $success"
puts "Fehler: $failed"
if {$failed == 0} {
    puts "✓ ALLE DIALOGE KORREKT GELADEN!"
}
