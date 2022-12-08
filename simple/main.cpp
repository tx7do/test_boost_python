#include <iostream>
#include <string>

#include <Python.h>
#include <boost/python.hpp>
namespace py = boost::python;

std::string parse_python_exception()
{
	PyObject * type_ptr = nullptr, *value_ptr = nullptr, *traceback_ptr = nullptr;
	::PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);

	std::string ret("Unfetchable Python error");
	if (type_ptr != nullptr)
	{
		py::handle<> h_type(type_ptr);
		py::str type_pstr(h_type);

		py::extract<std::string> e_type_pstr(type_pstr);
		if (e_type_pstr.check())
		{
			ret = e_type_pstr();
		}
		else
		{
			ret = "Unknown exception type";
		}
	}
	if (value_ptr != nullptr)
	{
		py::handle<> h_val(value_ptr);
		py::str a(h_val);
		py::extract<std::string> returned(a);
		if (returned.check())
		{
			ret += ": " + returned();
		}
		else
		{
			ret += std::string(": Unparseable Python error: ");
		}
	}

	if (traceback_ptr != nullptr)
	{
		py::handle<> h_tb(traceback_ptr);

		py::object
		tb(py::import("traceback"));
		py::object fmt_tb(tb.attr("format_tb"));
		py::object tb_list(fmt_tb(h_tb));
		py::object tb_str(py::str("\n").join(tb_list));
		py::extract<std::string> returned(tb_str);
		if (returned.check())
		{
			ret += ": " + returned();
		}
		else
		{
			ret += std::string(": Unparseable Python traceback");
		}
	}
	return ret;
}

int main()
{
	try
	{
		::Py_Initialize();

		py::object main_module = py::import("__main__");
		py::object main_namespace = main_module.attr("__dict__");

		// python 2.x 的print是关键字
		//py::exec("print 'Hello world python 2.7'", main_namespace);

		// python 3.x 的print是方法
		py::exec("print('Hello world python 3.0')", main_namespace);

		::Py_Finalize();
	}
	catch (py::error_already_set& e)
	{
		std::cout << "Error in Python: " << parse_python_exception() << std::endl;
	}

	return 0;
}
