#ifndef PKENGINE_PKBEHAVIOUR_H
#define PKENGINE_PKBEHAVIOUR_H

namespace pkengine
{
	class CGameObject;
	class CPKEngine;

	class CPKBehaviour_Internal
	{
	public:
		CPKBehaviour_Internal(CGameObject* InOwner);

		virtual ~CPKBehaviour_Internal() {}

		virtual bool CheckConstruct() { return true; }

		inline CGameObject* GetOwner() const { return Owner; }

	protected:
		CGameObject* Owner;
	};

	class CPKBehaviour : public CPKBehaviour_Internal
	{
	public:
		CPKBehaviour(CGameObject* InOwner) : CPKBehaviour_Internal(InOwner) {}
		virtual ~CPKBehaviour() {}

		virtual void Update() {}
	};
}

#endif // !PKENGINE_PKBEHAVIOUR_H
