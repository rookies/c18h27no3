/*
 * padding_data_calculator.hpp
 * 
 * Copyright 2012 Robert Knauer <robert@privatdemail.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#ifndef PADDING_DATA_CALCULATOR_HPP
#	define PADDING_DATA_CALCULATOR_HPP
	
#	include <iostream>
	
	class PaddingDataCalculator
	{
		public:
			PaddingDataCalculator();
			virtual ~PaddingDataCalculator();
			
			/*
			 * Set screen width and height:
			*/
			void set_screen_w(double w);
			void set_screen_h(double h);
			/*
			 * Calculate:
			 * INFO: Use this only after calling set_screen_w() and set_screen_h()
			 *       and before using get_padding_x(), get_padding_y(), get_usable_w()
			 *       or get_usable_h()
			*/
			void calculate(void);
			/*
			 * Get X and Y padding:
			*/
			double get_padding_x(void);
			double get_padding_y(void);
			/*
			 * Get usable screen width and height:
			*/
			double get_usable_w(void);
			double get_usable_h(void);
		private:
			/*
			 * Internal variables:
			*/
			double m_screen_w;
			double m_screen_h;
			double m_padding_x;
			double m_padding_y;
			double m_usable_w;
			double m_usable_h;
	};
#endif // PADDING_DATA_CALCULATOR_HPP
