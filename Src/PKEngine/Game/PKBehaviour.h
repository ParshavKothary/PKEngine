#ifndef PKENGINE_PKBEHAVIOUR_H
#define PKENGINE_PKBEHAVIOUR_H

namespace pkengine
{
	class CGameObject;
	class CPKEngine;

	class CPKBehaviour
	{
		friend CPKEngine;

	public:
		CPKBehaviour(CGameObject* InOwner);
		virtual ~CPKBehaviour() {}

		inline CGameObject* GetOwner() const { return Owner; }

	protected:

		virtual void Init() {}
		virtual void Update() {}

		CGameObject* Owner;
	};
}

#endif // !PKENGINE_PKBEHAVIOUR_H
