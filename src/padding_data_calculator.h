#ifndef _padding_data_calculator_h_
#	define _padding_data_calculator_h_
	
#	include <iostream>
	
	class PaddingDataCalculator
	{
		public:
			PaddingDataCalculator();
			~PaddingDataCalculator();
			
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
#endif // _padding_data_calculator_h_
