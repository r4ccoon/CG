cmake_minimum_required(VERSION 2.6)
project(Raytracer)

add_executable(Raytracer
	array.h
	camera.h
	light.cpp
	light.h
	main.cpp
	object.cpp
	object.h
	plane.cpp
	plane.h
	ppmgl2d.h
	ray.h
	raytracer.cpp
	raytracer.h
	sphere.cpp
	sphere.h
	vec3.h
)
