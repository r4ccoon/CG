#include <stdio.h>
#include "sphere.h"
#include "plane.h"
#include "ray.h"
#include "raytracer.h"

RayTracer *rt;

// ============================================================================
//    SCENE 1, NO TRANSPARENCY
// ============================================================================
void initScene1()
{
	Vec3d eye, look, up, sp;
	double fov;
	Vec3d ambient, diffuse, specular;
	bool reflective, transparent;

	// REFLECTIVE BALLS
	Sphere *s;
	ambient .Set(0.035, 0.0325, 0.025),
	diffuse .Set(0.9  , 0.9   , 0.9 ),
	specular.Set(0.9  , 0.9   , 0.9  );
	reflective  = true;
	transparent = false;

	double kd = 1.7, ks = 0.4, kt = 0.6, kn = 1.1;

	sp.Set(0.272166, 0.272166, 0.544331);
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(0.643951, 0.172546, 0 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(0.172546, 0.643951, 0 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(-0.371785, 0.0996195, 0.544331 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(-0.471405, 0.471405, 0 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(-0.643951, -0.172546, 0 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(0.0996195, -0.371785, 0.544331 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(-0.172546, -0.643951, 0 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(0.471405, -0.471405, 0 );
	s = new Sphere(sp,0.166667, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);
	sp.Set(0, 0, 0);
	s = new Sphere(sp,0.5, ambient, diffuse, specular, reflective, transparent, kd,ks,kt,kn);
	rt->AddObject(s);

	// DIFFUSE GROUND PLANE
	Plane *p;
	Vec3d pos(0,0,-0.5), norm(0,0,1);
	ambient.Set(0.15, 0.1 , 0.04);
	diffuse.Set(1.0 , 0.75, 0.33);
	reflective  = false;
	transparent = false;
	p = new Plane(pos, norm, ambient, diffuse, specular, reflective, transparent);
	rt->AddObject(p);

	// CAMERA
	eye .Set(2.1, 1.3, 1.7);
	look.Set(0,0,0);
	up  .Set(0,0,1);
	fov = 22.5; // half opening angle of viewing frustum
	rt->SetCamera(eye,look,up,fov);
	rt->SetBackground(0.078, 0.361, 0.753);
}

void initLights1()
{
	Light *l;
	l = new Light(Vec3d(4,3,2));
	l->Intensity(0.288675);
	rt->AddLight(l);
	l = new Light(Vec3d(1,-4,4));
	l->Intensity(0.288675);
	rt->AddLight(l);
	l = new Light(Vec3d(-3,1,5));
	l->Intensity(0.288675);
	rt->AddLight(l);
}

// ============================================================================
//    SCENE 2, TRANSPARENCY
// ============================================================================
void initScene2()
{
	Vec3d eye, look, up, sp;
	Vec3d ambient, diffuse, specular;
	bool reflective, transparent;
	double fov, kn, kd, ks, kt;
	Sphere *s;

	// GLASS BALL
	ambient .Set(0.017678, 0.017678, 0.017678);
	diffuse .Set(0.1     , 0.1     , 0.1     );
	specular.Set(1,1,1);
	reflective  = true;
	transparent = true;
	kn = 0.8;
	kd = 0.4;
	ks = 0.4;
	kt = 0.6;
	sp.Set(0, 0, 1.2);
	s = new Sphere(sp,0.5, ambient, diffuse, specular, reflective, transparent,
		           kd,ks,kt,kn);
	s->Shininess(500.0);
	rt->AddObject(s);

	// SECOND GLASS BALL
	ambient .Set(0.017678, 0.017678, 0.017678);
	diffuse .Set(0.1     , 0.1     , 0.1     );
	specular.Set(1,1,1);
	reflective  = true;
	transparent = true;
	kn = 1/kn; //1.95;
	kd = 0.4;
	ks = 0.4;
	kt = 0.6;
	sp.Set(0, 0, 1.2);
	s = new Sphere(sp,0.48, ambient, diffuse, specular, reflective, transparent,
		           kd,ks,kt,kn);
	s->Shininess(500.0);
	rt->AddObject(s);

	// RED BALL
	ambient .Set(0.35, 0.0325, 0.025);
	diffuse .Set(0.8 , 0.05  , 0.05 );
	specular.Set(0.2 , 0.2   , 0.2  );
	reflective  = false;
	transparent = false;
	sp.Set(-0.75, 0.5, 0.2);
	s = new Sphere(sp,0.5, ambient, diffuse, specular, reflective, transparent);
	rt->AddObject(s);

	// DIFFUSE GROUND PLANE
	Plane *p;
	Vec3d pos(0,0,-0.5), norm(0,0,1);
	ambient.Set(0.15, 0.1 , 0.04);
	diffuse.Set(1   , 0.75, 0.33);
	reflective  = false;
	transparent = false;
	p = new Plane(pos, norm, 1.5*ambient, 1.5*diffuse, specular, reflective, transparent);
	rt->AddObject(p);

	// CAMERA
	eye .Set(2,-1.5,1.9);
	look.Set(-0.75, 0.5, 0.4);
	up  .Set(0,0,1);
	fov = 22.5; // half opening angle of viewing frustum
	rt->SetCamera(eye,look,up,fov);
	rt->SetBackground(0.078, 0.361, 0.753);
}

void initLights2()
{
	Light *l;
	l = new Light(Vec3d(4,3,2));
	l->Intensity(0.3288675);
	rt->AddLight(l);
	l = new Light(Vec3d(1,-4,4));
	l->Intensity(0.3288675);
	rt->AddLight(l);
	l = new Light(Vec3d(-3,1,5));
	l->Intensity(0.3288675);
	rt->AddLight(l);
}


// ============================================================================
//    MAIN
// ============================================================================

// CHOOSE BETWEEN RENDERING SCENE 1 OR 2
#define RENDER_SCENE 1

int main()
{
	rt = new RayTracer(512,512);

#if RENDER_SCENE == 1
	initScene1();
	initLights1();
	rt->Render("scene1.ppm");
#else
	initScene2();
	initLights2();
	rt->Render("scene2.ppm");
#endif

	delete rt;

	return 0;
}
