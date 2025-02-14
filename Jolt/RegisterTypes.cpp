// Jolt Physics Library (https://github.com/jrouwe/JoltPhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#include <Jolt/Jolt.h>

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/RTTI.h>
#include <Jolt/Physics/Collision/CollisionDispatch.h>
#include <Jolt/Physics/Collision/Shape/TriangleShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/TaperedCapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/CylinderShape.h>
#include <Jolt/Physics/Collision/Shape/ScaledShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/Shape/ConvexHullShape.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Jolt/Physics/Collision/Shape/MutableCompoundShape.h>
#include <Jolt/Physics/Collision/Shape/StaticCompoundShape.h>
#include <Jolt/Physics/Collision/PhysicsMaterialSimple.h>
#include <Jolt/Physics/SoftBody/SoftBodyShape.h>

JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, Skeleton)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, SkeletalAnimation)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, CompoundShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, StaticCompoundShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, MutableCompoundShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, TriangleShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, SphereShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, BoxShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, CapsuleShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, TaperedCapsuleShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, CylinderShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, ScaledShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, MeshShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, ConvexHullShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, HeightFieldShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, RotatedTranslatedShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, OffsetCenterOfMassShapeSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, RagdollSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, PointConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, SixDOFConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, SliderConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, SwingTwistConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, DistanceConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, HingeConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, FixedConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, ConeConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, PathConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, PathConstraintPath)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, PathConstraintPathHermite)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, VehicleConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, WheeledVehicleControllerSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, RackAndPinionConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, GearConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, PulleyConstraintSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, MotorSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, PhysicsScene)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, PhysicsMaterial)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, GroupFilter)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, GroupFilterTable)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, BodyCreationSettings)
JPH_DECLARE_RTTI_WITH_NAMESPACE_FOR_FACTORY(JPH_EXPORT, JPH, SoftBodyCreationSettings)

JPH_NAMESPACE_BEGIN

bool VerifyJoltVersionIDInternal(uint64 inVersionID)
{
	return inVersionID == JPH_VERSION_ID;
}

void RegisterTypesInternal(uint64 inVersionID)
{
	// Version check
	if (!VerifyJoltVersionIDInternal(inVersionID))
	{
		JPH_ASSERT(false, "Version mismatch, make sure you compile the client code with the same Jolt version and compiler definitions!");
		JPH_CRASH;
	}

#ifndef JPH_DISABLE_CUSTOM_ALLOCATOR
	JPH_ASSERT(Allocate != nullptr && Free != nullptr && AlignedAllocate != nullptr && AlignedFree != nullptr, "Need to supply an allocator first or call RegisterDefaultAllocator()");
#endif // !JPH_DISABLE_CUSTOM_ALLOCATOR

	JPH_ASSERT(Factory::sInstance != nullptr, "Need to create a factory first!");

	// Initialize dispatcher
	CollisionDispatch::sInit();

	// Register base classes first so that we can specialize them later
	CompoundShape::sRegister();
	ConvexShape::sRegister();

	// Register compounds before others so that we can specialize them later (register them in reverse order of collision complexity)
	MutableCompoundShape::sRegister();
	StaticCompoundShape::sRegister();

	// Leaf classes
	TriangleShape::sRegister();
	SphereShape::sRegister();
	BoxShape::sRegister();
	CapsuleShape::sRegister();
	TaperedCapsuleShape::sRegister();
	CylinderShape::sRegister();
	MeshShape::sRegister();
	ConvexHullShape::sRegister();
	HeightFieldShape::sRegister();
	SoftBodyShape::sRegister();

	// Register these last because their collision functions are simple so we want to execute them first (register them in reverse order of collision complexity)
	RotatedTranslatedShape::sRegister();
	OffsetCenterOfMassShape::sRegister();
	ScaledShape::sRegister();

	// Create list of all types
	const RTTI *types[] = {
		JPH_RTTI(SkeletalAnimation),
		JPH_RTTI(Skeleton),
		JPH_RTTI(CompoundShapeSettings),
		JPH_RTTI(StaticCompoundShapeSettings),
		JPH_RTTI(MutableCompoundShapeSettings),
		JPH_RTTI(TriangleShapeSettings),
		JPH_RTTI(SphereShapeSettings),
		JPH_RTTI(BoxShapeSettings),
		JPH_RTTI(CapsuleShapeSettings),
		JPH_RTTI(TaperedCapsuleShapeSettings),
		JPH_RTTI(CylinderShapeSettings),
		JPH_RTTI(ScaledShapeSettings),
		JPH_RTTI(MeshShapeSettings),
		JPH_RTTI(ConvexHullShapeSettings),
		JPH_RTTI(HeightFieldShapeSettings),
		JPH_RTTI(RotatedTranslatedShapeSettings),
		JPH_RTTI(OffsetCenterOfMassShapeSettings),
		JPH_RTTI(RagdollSettings),
		JPH_RTTI(PointConstraintSettings),
		JPH_RTTI(SixDOFConstraintSettings),
		JPH_RTTI(SliderConstraintSettings),
		JPH_RTTI(SwingTwistConstraintSettings),
		JPH_RTTI(DistanceConstraintSettings),
		JPH_RTTI(HingeConstraintSettings),
		JPH_RTTI(FixedConstraintSettings),
		JPH_RTTI(ConeConstraintSettings),
		JPH_RTTI(PathConstraintSettings),
		JPH_RTTI(VehicleConstraintSettings),
		JPH_RTTI(WheeledVehicleControllerSettings),
		JPH_RTTI(PathConstraintPath),
		JPH_RTTI(PathConstraintPathHermite),
		JPH_RTTI(RackAndPinionConstraintSettings),
		JPH_RTTI(GearConstraintSettings),
		JPH_RTTI(PulleyConstraintSettings),
		JPH_RTTI(MotorSettings),
		JPH_RTTI(PhysicsScene),
		JPH_RTTI(PhysicsMaterial),
		JPH_RTTI(PhysicsMaterialSimple),
		JPH_RTTI(GroupFilter),
		JPH_RTTI(GroupFilterTable),
		JPH_RTTI(BodyCreationSettings),
		JPH_RTTI(SoftBodyCreationSettings)
	};

	// Register them all
	Factory::sInstance->Register(types, (uint)size(types));

	// Initialize default physics material
	if (PhysicsMaterial::sDefault == nullptr)
		PhysicsMaterial::sDefault = new PhysicsMaterialSimple("Default", Color::sGrey);
}

void UnregisterTypes()
{
	// Unregister all types
	if (Factory::sInstance != nullptr)
		Factory::sInstance->Clear();

	// Delete default physics material
	PhysicsMaterial::sDefault = nullptr;
}

JPH_NAMESPACE_END
