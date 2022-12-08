#include <iostream>
#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/operators.h>
#include <pybind11/eval.h>
#include <pybind11/stl.h>
namespace py = pybind11;

int main()
{
	py::scoped_interpreter guard{};

	try
	{
		py::exec(
			"print('Hello')\n"
			"print('world!');",
			py::globals());
	}
	catch (py::error_already_set& e)
	{
		std::cout << "Error in Python: " << e.what() << std::endl;
	}

	return 0;
}
