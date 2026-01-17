#----------------------------------------------------------------------------
# Tools
#----------------------------------------------------------------------------
proc dialog { w title text bitmap default args } {
    global button
    
    # Top-level-Window
    toplevel $w -class Dialog
    wm title $w $title
    wm iconname $w Dialog
    # wm transient $w .
    frame $w.top -relief raised -bd 1
    pack $w.top -side top -fill both
    frame $w.bot -relief raised -bd 1
    pack $w.bot -side bottom -fill both

    # Message und Buttons
    message $w.top.msg -width 3i -text $text\
            -font -Adobe-Times-Medium-R-Normal-*-140-*
    pack $w.top.msg -side right -expand 1 -fill both -padx 3m -pady 3m
    if {$bitmap != ""} {
        label $w.top.bitmap -bitmap $bitmap
        pack $w.top.bitmap -side left -padx 3m -pady 3m
    }

    # Buttons
    set i 0
    foreach but $args {
        button $w.bot.button$i -text $but -command "set button $i"
        if {$i==$default} {
            frame $w.bot.default -relief sunken -bd 1
            raise $w.bot.button$i
            pack $w.bot.default -side left -expand 1 -padx 3m -pady 2m
            pack $w.bot.button$i -in $w.bot.default -side left -padx 2m -pady 2m -ipadx 2m -ipady 1m
        } else {
            pack $w.bot.button$i -side left -expand 1 -padx 3m -pady 3m -ipadx 2m -ipady 1m
        }
        incr i
    }

    #Bindings
    if {$default >= 0} {
        bind $w <Return> "$w.bot.button$default flash; set button $default"
    }
    set oldFocus [focus]
    grab set $w
    focus $w

    # Waiting...
    tkwait variable button
    destroy $w
    focus $oldFocus
    return $button
    
}

