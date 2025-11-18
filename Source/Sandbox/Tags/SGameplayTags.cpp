#include "SGameplayTags.h"

namespace Sandbox
{
	// Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "Input.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip, "Input.Unequip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe, "Input.LightAttack.Axe");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Axe, "Input.HeavyAttack.Axe");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "Input.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "Input.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dash, "Input.Dash");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "Input.SwitchTarget");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "Input.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "Input.MustBeHeld.Block");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "Input.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "Input.Toggleable.TargetLock");

	// Player Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_LightSword, "Player.Ability.Equip.LightSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_GreatSword, "Player.Ability.Equip.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_TwinSword, "Player.Ability.Equip.TwinSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe, "Player.Ability.Unequip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_LightSword, "Player.Ability.Unequip.LightSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_GreatSword, "Player.Ability.Unequip.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_TwinSword, "Player.Ability.Unequip.TwinSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe, "Player.Ability.Attack.Light.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Axe, "Player.Ability.Attack.Heavy.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dash, "Player.Ability.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");

	// Weapon Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_SwordAndShield, "Player.Weapon.SwordAndShield");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_GreatSword, "Player.Weapon.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_TwinSword, "Player.Weapon.TwinSword");

	// Events
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equipped, "Player.Event.Weapon.Equipped.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equipped_LightSword, "Player.Event.Weapon.Equipped.LightSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equipped_GreatSword, "Player.Event.Weapon.Equipped.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equipped_TwinSword, "Player.Event.Weapon.Equipped.TwinSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Unequipped, "Player.Event.Weapon.Unequipped.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Unequipped_LightSword, "Player.Event.Weapon.Unequipped.LightSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Unequipped_GreatSword, "Player.Event.Weapon.Unequipped.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Unequipped_TwinSword, "Player.Event.Weapon.Unequipped.TwinSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_LightAttack, "Player.Event.Weapon.LightAttack.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_HeavyAttack, "Player.Event.Weapon.HeavyAttack.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessfulBlock, "Player.Event.SuccessfulBlock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left, "Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right, "Player.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_LevelUp, "Player.Event.LevelUp");

	// Status Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jumping, "Player.Status.Jumping");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dashing, "Player.Status.Dashing");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blocking, "Player.Status.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Equipped_LightSword, "Player.Status.Equipped.LightSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Equipped_GreatSword, "Player.Status.Equipped.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Equipped_TwinSword, "Player.Status.Equipped.TwinSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock, "Player.Status.TargetLock");

	// Attack Types
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");


	// Enemy Tags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_DrawHealthBar, "Enemy.Ability.DrawHealthBar");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Unblockable, "Enemy.Status.Unblockable");
	

	// Shared Event Tags
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Killed, "Shared.Event.Killed");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Exhausted, "Shared.Event.Exhausted");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_NoMana, "Shared.Event.NoMana");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	// Shared Ability Tags
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_OnGiven, "Shared.Ability.OnGiven");

	// Shared Status Tags
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");

	FName const Sandbox::Player(TEXT("Player"));	
}