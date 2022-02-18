# RevKit: A Toolkit for Reversible Circuit Design (www.revkit.org)
# Copyright (C) 2009-2011  The RevKit Developers <revkit@informatik.uni-bremen.de>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#from revkit_python import *
#from algorithm import *
from mqt.syrec import *
def error_msg( statistics ):
    "Returns the error message contained in statistics"
    return "Error: " + statistics.get_string( "error", "" )

def read_programi( prog, filename, default_bitwidth = 32 ):
    "Reads a SyReC program from a file"
    settings = read_program_settingsi()
    settings.default_bitwidth = default_bitwidth
    e = py_read_programi( prog, filename, settings )
    if e == "":
        return True
    else:
        return e

### CORE/UTILS


### ALGORITHMS

def syrec_synthesisi( circ, prog, variable_name_format = "%1$s%3$s.%2$d", main_module = "", if_realization = 0, efficient_controls = True, modules_hierarchy = False ):
    # TODO implement functor
    "SyReC Synthesis"
    settings = propertiesi()
    settings.set_string( "variable_name_format", variable_name_format )
   
    settings.set_string( "main_module", main_module )
    settings.set_unsigned( "if_realization", if_realization )
    settings.set_bool( "efficient_controls", efficient_controls )
    
    settings.set_bool( "modules_hierarchy", modules_hierarchy )
    statistics = propertiesi()

    if py_syrec_synthesisi( circ, prog, settings, statistics ):
        return dict( runtime = statistics.get_double( "runtime" ) )
    else:
        return error_msg( statistics )

### GUI
def init_gui():
    from PyQt4 import QtGui
    return QtGui.QApplication([])

def display_circuit( circ ):
    import revkitui

    w = revkitui.CircuitView( circ )
    w.setWindowTitle( "Circuit View" )
    w.show()
    return w
    #a.exec_()


