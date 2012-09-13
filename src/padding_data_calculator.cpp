#include "padding_data_calculator.h"

using namespace std;

PaddingDataCalculator::PaddingDataCalculator()
{
	
}
PaddingDataCalculator::~PaddingDataCalculator()
{
	
}
void PaddingDataCalculator::set_screen_w(double w)
{
	m_screen_w = w;
}
void PaddingDataCalculator::set_screen_h(double h)
{
	m_screen_h = h;
}
void PaddingDataCalculator::calculate(void)
{
	cout << "Calculating padding data... ";
	m_padding_x = 0;
	m_padding_y = 0;
	m_usable_w = m_screen_w;
	m_usable_h = m_screen_h;
	if (m_screen_h*(16.0/9.0) < m_screen_w)
	{
		// x padding needed
		m_padding_y = 0;
		m_usable_w = m_screen_h*(16.0/9.0);
		m_usable_h = m_screen_h;
		m_padding_x = (m_screen_w - m_usable_w)/2.0;
	}
	else if (m_screen_h*(16.0/9.0) > m_screen_w)
	{
		// y padding needed
		m_padding_x = 0;
		m_usable_w = m_screen_w;
		m_usable_h = m_screen_w*(9.0/16.0);
		m_padding_y = (m_screen_h - m_usable_h)/2.0;
	};
	cout << "[DONE]" << endl;
	cout << "Padding Data:" << endl;
	cout << "  X Padding: " << m_padding_x << endl;
	cout << "  Y Padding: " << m_padding_y << endl;
	cout << "  Usable W: " << m_usable_w << endl;
	cout << "  Usable H: " << m_usable_h << endl;
}
double PaddingDataCalculator::get_padding_x(void)
{
	return m_padding_x;
}
double PaddingDataCalculator::get_padding_y(void)
{
	return m_padding_y;
}
double PaddingDataCalculator::get_usable_w(void)
{
	return m_usable_w;
}
double PaddingDataCalculator::get_usable_h(void)
{
	return m_usable_h;
}
