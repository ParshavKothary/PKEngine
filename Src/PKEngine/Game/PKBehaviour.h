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
		virtual void Update() {}

	protected:

		virtual void Init() {}

		CGameObject* Owner;
	};
}

#endif // !PKENGINE_PKBEHAVIOUR_H
