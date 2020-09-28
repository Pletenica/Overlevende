#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());
	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();
	chassis.color = White;

	Cube backdecoration(info.backdecoration_size.x, info.backdecoration_size.y, info.backdecoration_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&backdecoration.transform);
	btVector3 offsetfrontdecoration(info.backdecoration_offset.x, info.backdecoration_offset.y, info.backdecoration_offset.z);
	offsetfrontdecoration = offsetfrontdecoration.rotate(q.getAxis(), q.getAngle());
	backdecoration.transform.M[12] += offsetfrontdecoration.getX();
	backdecoration.transform.M[13] += offsetfrontdecoration.getY();
	backdecoration.transform.M[14] += offsetfrontdecoration.getZ();
	backdecoration.color = White;

	Cube frontdecoration(info.frontdecoration_size.x, info.frontdecoration_size.y, info.frontdecoration_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&frontdecoration.transform);
	btVector3 offsetbackdecoration(info.frontdecoration_offset.x, info.frontdecoration_offset.y, info.frontdecoration_offset.z);
	offsetbackdecoration = offsetbackdecoration.rotate(q.getAxis(), q.getAngle());
	frontdecoration.transform.M[12] += offsetbackdecoration.getX();
	frontdecoration.transform.M[13] += offsetbackdecoration.getY();
	frontdecoration.transform.M[14] += offsetbackdecoration.getZ();
	frontdecoration.color = White;


	Cube frontwall(info.frontwall_size.x, info.frontwall_size.y, info.frontwall_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&frontwall.transform);
	btVector3 offsetfrontwall(info.frontwall_offset.x, info.frontwall_offset.y, info.frontwall_offset.z);
	offsetfrontwall = offsetfrontwall.rotate(q.getAxis(), q.getAngle());
	frontwall.transform.M[12] += offsetfrontwall.getX();
	frontwall.transform.M[13] += offsetfrontwall.getY();
	frontwall.transform.M[14] += offsetfrontwall.getZ();
	frontwall.color = White;

	Cube backwall(info.backwall_size.x, info.backwall_size.y, info.backwall_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&backwall.transform);
	btVector3 offsetbackwall(info.backwall_offset.x, info.backwall_offset.y, info.backwall_offset.z);
	offsetbackwall = offsetbackwall.rotate(q.getAxis(), q.getAngle());
	backwall.transform.M[12] += offsetbackwall.getX();
	backwall.transform.M[13] += offsetbackwall.getY();
	backwall.transform.M[14] += offsetbackwall.getZ();
	backwall.color = White;

	Cube stick1(info.stick1_size.x, info.stick1_size.y, info.stick1_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stick1.transform);
	btVector3 offsetstick1(info.stick1_offset.x, info.stick1_offset.y, info.stick1_offset.z);
	offsetstick1 = offsetstick1.rotate(q.getAxis(), q.getAngle());
	stick1.transform.M[12] += offsetstick1.getX();
	stick1.transform.M[13] += offsetstick1.getY();
	stick1.transform.M[14] += offsetstick1.getZ();
	stick1.color = White;

	Cube stick2(info.stick2_size.x, info.stick2_size.y, info.stick2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stick2.transform);
	btVector3 offsetstick2(info.stick2_offset.x, info.stick2_offset.y, info.stick2_offset.z);
	offsetstick2 = offsetstick2.rotate(q.getAxis(), q.getAngle());
	stick2.transform.M[12] += offsetstick2.getX();
	stick2.transform.M[13] += offsetstick2.getY();
	stick2.transform.M[14] += offsetstick2.getZ();
	stick2.color = White;

	Cube stick3(info.stick3_size.x, info.stick3_size.y, info.stick3_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stick3.transform);
	btVector3 offsetstick3(info.stick3_offset.x, info.stick3_offset.y, info.stick3_offset.z);
	offsetstick3 = offsetstick3.rotate(q.getAxis(), q.getAngle());
	stick3.transform.M[12] += offsetstick3.getX();
	stick3.transform.M[13] += offsetstick3.getY();
	stick3.transform.M[14] += offsetstick3.getZ();
	stick3.color = White;

	Cube stick4(info.stick4_size.x, info.stick4_size.y, info.stick4_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stick4.transform);
	btVector3 offsetstick4(info.stick4_offset.x, info.stick4_offset.y, info.stick4_offset.z);
	offsetstick4 = offsetstick4.rotate(q.getAxis(), q.getAngle());
	stick4.transform.M[12] += offsetstick4.getX();
	stick4.transform.M[13] += offsetstick4.getY();
	stick4.transform.M[14] += offsetstick4.getZ();
	stick4.color = White;

	Cube techo(info.techo_size.x, info.techo_size.y, info.techo_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&techo.transform);
	btVector3 offsettecho(info.techo_offset.x, info.techo_offset.y, info.techo_offset.z);
	offsettecho = offsettecho.rotate(q.getAxis(), q.getAngle());
	techo.transform.M[12] += offsettecho.getX();
	techo.transform.M[13] += offsettecho.getY();
	techo.transform.M[14] += offsettecho.getZ();
	techo.color = Purple;


	chassis.Render();
	backdecoration.Render();
	frontdecoration.Render();
	frontwall.Render();
	backwall.Render();
	stick1.Render();
	stick2.Render();
	stick3.Render();
	stick4.Render();
	techo.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

void PhysVehicle3D::ResetVelocityAndRotation() {
	vehicle->getRigidBody()->setAngularVelocity({ 0,0,0 });
	vehicle->getRigidBody()->setLinearVelocity({ 0,0,0 });
	btTransform t = vehicle->getRigidBody()->getWorldTransform();
	t.setRotation({ 0,0,0,1 });
	vehicle->getRigidBody()->setWorldTransform(t);
}