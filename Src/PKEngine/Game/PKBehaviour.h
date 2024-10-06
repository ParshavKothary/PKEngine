#ifndef PKENGINE_PKBEHAVIOUR_H
#define PKENGINE_PKBEHAVIOUR_H

namespace pkengine
{
	class CGameObject;
	class CPKEngine;

	class CBehaviour_Internal
	{
	public:
		CBehaviour_Internal(CGameObject* InOwner);

		virtual ~CBehaviour_Internal() {}

		virtual bool CheckConstruct() { return true; }

		inline CGameObject* GetOwner() const { return Owner; }

	protected:
		CGameObject* Owner;
	};

	class CBehaviour : public CBehaviour_Internal
	{
	public:
		CBehaviour(CGameObject* InOwner) : CBehaviour_Internal(InOwner) {}
		virtual ~CBehaviour() {}

		virtual void Update() {}
	};
}

#endif // !PKENGINE_PKBEHAVIOUR_H
