/*
Copyright (C) 2011 Georgia Institute of Technology

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <electric-synapse.h>

extern "C" Plugin::Object *createRTXIPlugin(void) {
	return new ElecSyn();
}

// inputs, outputs, parameters
static DefaultGUIModel::variable_t vars[] = {
	{"Vm 1", "V", DefaultGUIModel::INPUT, },
	{"Vm 2", "V", DefaultGUIModel::INPUT, },
	{"Im 1", "A", DefaultGUIModel::OUTPUT, },
	{"Im 2", "A", DefaultGUIModel::OUTPUT, },
	{"Conductance (S)", "Conductance of the simulated synapse (S)", DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE, },
};

// some necessary variable
static size_t num_vars = sizeof(vars) / sizeof(DefaultGUIModel::variable_t);

// constructor
// provides default values for paramters, calls update(INIT)
ElecSyn::ElecSyn(void) : DefaultGUIModel("Electrical Synapse",::vars,::num_vars) {
	setWhatsThis( "<p><b>Electrical Synapse:</b><br>This module creates an electrical connection between two cells.</p>" );
	createGUI(vars, num_vars);
	initParameters();
	update(INIT);
	refresh();
	resizeMe();
}

ElecSyn::~ElecSyn(void) {}

// execute is run every time step
void ElecSyn::execute(void) {
	systime = count * dt; // time in seconds
	Vm1 = input(0); // V
	Vm2 = input(1);
	Im1 = G*(Vm2-Vm1); // A
	Im2 = G*(Vm1-Vm2); // A
	output(0) = Im1;
	output(1) = Im2;
	count++;
}

void ElecSyn::update(DefaultGUIModel::update_flags_t flag) {
	switch(flag) {
		case INIT:
			setParameter("Conductance (S)", QString::number(G));
			break;

		case MODIFY:
			G = getParameter("Conductance (S)").toDouble();
			break;

		case PAUSE:
			output(0) = 0.0;
			output(1) = 0.0;
			break;

		case UNPAUSE:
			count = 0;
			systime = 0;
			break;

		case PERIOD:
			dt = RT::System::getInstance()->getPeriod() * 1e-9; // s
			break;

		default:
			break;
	}
}

void ElecSyn::initParameters() {
	G = 1e-9;
	dt = RT::System::getInstance()->getPeriod() * 1e-9; // s
	systime = 0;
	count = 0;
}
