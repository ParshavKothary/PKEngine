#ifndef PKENGINE_PKBEHAVIOUR_H
#define PKENGINE_PKBEHAVIOUR_H

namespace pkengine
{
	class CGameObject;
	class CPKEngine;

	class CBehaviour
	{
	public:
		CBehaviour(CGameObject* InOwner);

		virtual ~CBehaviour() {}

		virtual bool CheckConstruct() { return true; }

		inline CGameObject* GetOwner() const { return Owner; }

		virtual void Update() {}

	protected:
		CGameObject* Owner;
	};
}

#endif // !PKENGINE_PKBEHAVIOUR_H
