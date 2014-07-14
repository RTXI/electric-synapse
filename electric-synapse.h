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

/*
* Electrical synapse
*/

#include <default_gui_model.h>

class ElecSyn : public DefaultGUIModel {
	
	public:
	
		ElecSyn(void);
		virtual ~ElecSyn(void);
	
	// the main function run every time step, contains model logic
		virtual void execute(void);
	
	protected:
	
	// run each time model parameters are updated
		virtual void update(DefaultGUIModel::update_flags_t);
	
	private:
	
		void initParameters();
	
	// parameters
		double G;
		double Vm1;
		double Vm2;
		double Im1;
		double Im2;

		double dt; // system period
		double systime;
		long long count;
};
