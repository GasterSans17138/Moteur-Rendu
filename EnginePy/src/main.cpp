#include <Maths/Vec2.hpp>
#include <Maths/Vec3.hpp>

#include <DataStructure/GameObject.hpp>

#include <LowRenderer/Camera.hpp>

#include <PlayerCommon.hpp>

#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

//---------------- Notes ----------------
//
// We only defined the bare minimum needed for scripts to work (time constraint)
//
//---------------------------------------

PYBIND11_MODULE(EnginePy, m)
{
	m.doc() = "[EnginePy] : Python library to program \"The binding of python !\" Have fun !";

#pragma region Vec3
	pybind11::class_<Core::Maths::Vec3>(m, "Vec3")
		//Constructor
		.def(pybind11::init<float, float, float>(), pybind11::arg("x") = 0.f, pybind11::arg("y") = 0.f, pybind11::arg("z") = 0.f) 
		.def(pybind11::init<Core::Maths::Vec3>())
		
		//Methods
		.def("DotProduct", &Core::Maths::Vec3::DotProduct)
		.def("Magnitude", &Core::Maths::Vec3::Magnitude)
		.def("CrossProduct", &Core::Maths::Vec3::CrossProduct)
		.def("Normalize", &Core::Maths::Vec3::Normalize)

		//Operators
		.def(pybind11::self + pybind11::self)
		.def(pybind11::self - pybind11::self)
		.def(pybind11::self * float())
		.def(pybind11::self / float())
		.def(pybind11::self += pybind11::self)
		.def(pybind11::self -= pybind11::self)
		.def(pybind11::self *= float())
		.def(pybind11::self /= float())

		.def(pybind11::self == pybind11::self)
		.def(pybind11::self != pybind11::self)
		.def(pybind11::self < pybind11::self)
		.def(pybind11::self <= pybind11::self)
		.def(pybind11::self > pybind11::self)
		.def(pybind11::self >= pybind11::self)
		
		//.def(pybind11::self *= pybind11::self) <- dont compile

		//Atributes
		.def_readwrite("x", &Core::Maths::Vec3::x)
		.def_readwrite("y", &Core::Maths::Vec3::y)
		.def_readwrite("z", &Core::Maths::Vec3::z)
		.def("__repr__", &Core::Maths::Vec3::toString);

#pragma endregion Core::Maths::Vec3	

#pragma region Vec2
	pybind11::class_<Core::Maths::Vec2>(m, "Vec2")
		//Constructor
		.def(pybind11::init<float, float>(), pybind11::arg("x") = 0.f, pybind11::arg("y") = 0.f)
		.def(pybind11::init<Core::Maths::Vec2>())

		//Methods
		.def("DotProduct", &Core::Maths::Vec2::DotProduct)
		.def("Magnitude", &Core::Maths::Vec2::Magnitude)
		.def("CrossProduct", &Core::Maths::Vec2::CrossProduct)
		.def("Normalize", &Core::Maths::Vec2::Normalize)

		//Operators
		.def(pybind11::self + pybind11::self)
		.def(pybind11::self - pybind11::self)
		.def(pybind11::self * float())
		.def(pybind11::self / float())
		.def(pybind11::self += pybind11::self)
		.def(pybind11::self -= pybind11::self)
		.def(pybind11::self *= float())
		.def(pybind11::self /= float())

		.def(pybind11::self == pybind11::self)
		.def(pybind11::self != pybind11::self)
		.def(pybind11::self < pybind11::self)
		.def(pybind11::self <= pybind11::self)
		.def(pybind11::self > pybind11::self)
		.def(pybind11::self >= pybind11::self)

		//Atributes
		.def_readwrite("x", &Core::Maths::Vec2::x)
		.def_readwrite("y", &Core::Maths::Vec2::y)
		.def("__repr__", &Core::Maths::Vec2::toString); //repr is representation like print

#pragma endregion Core::Maths::Vec2

#pragma region GameObject
	pybind11::class_<DataStructure::GameObject>(m, "GameObject")
		.def_readwrite("velocity", &DataStructure::GameObject::Velocity);
#pragma endregion DataStructure::GameObject

#pragma region Camera
	pybind11::class_<LowRenderer::Camera>(m, "Camera")
		.def_readwrite("Front", &LowRenderer::Camera::Front)
		.def_readwrite("Right", &LowRenderer::Camera::Right);
#pragma endregion LowRendrer::Camera

#pragma region PlayerInputs
	pybind11::class_<PlayerInputs>(m, "PlayerInputs")
		.def_readonly("moveForward", &PlayerInputs::moveForward)
		.def_readonly("moveBackward", &PlayerInputs::moveBackward)
		.def_readonly("moveRight", &PlayerInputs::moveBackward)
		.def_readonly("moveRight", &PlayerInputs::moveRight)
		.def_readonly("moveLeft", &PlayerInputs::moveLeft)
		.def_readonly("moveJump", &PlayerInputs::moveJump);
#pragma endregion PlayerInputs
}

/*
TODO : 
	bool canJump
*/