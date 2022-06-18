#ifndef _MMATCHRULE_DEATHMATCH_H
#define _MMATCHRULE_DEATHMATCH_H


#include "MMatchRule.h"
#include <d3d9.h>

class MMatchRuleSoloDeath : public MMatchRule {
protected:
	bool CheckKillCount(MMatchObject* pOutObject);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual void OnRoundTimeOut();
	virtual bool OnCheckRoundFinish();
	virtual bool RoundCount();
public:
	MMatchRuleSoloDeath(MMatchStage* pStage);
	virtual ~MMatchRuleSoloDeath() { }
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_DEATHMATCH_SOLO; }
};

///////////////////////////////////////////////////////////////////////////////////////////////
class MMatchRuleTeamDeath : public MMatchRule {
protected:
	bool GetAliveCount(int* pRedAliveCount, int* pBlueAliveCount);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual bool OnRun();
	virtual void OnRoundBegin();
	virtual void OnRoundEnd();
	virtual bool OnCheckRoundFinish();
	virtual void OnRoundTimeOut();
	virtual bool RoundCount();
	virtual bool OnCheckEnableBattleCondition();
public:
	MMatchRuleTeamDeath(MMatchStage* pStage);
	virtual ~MMatchRuleTeamDeath()				{}
	virtual void CalcTeamBonus(MMatchObject* pAttacker, MMatchObject* pVictim,
								int nSrcExp, int* poutAttackerExp, int* poutTeamExp);
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_DEATHMATCH_TEAM; }
};


// �߰� by ����
///////////////////////////////////////////////////////////////////////////////////////////////
class MMatchRuleTeamDeath2 : public MMatchRule {
protected:
	void GetTeamScore(int* pRedTeamScore, int* pBLueTeamScore);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual bool OnRun();
	virtual void OnRoundBegin();
	virtual void OnRoundEnd();
	virtual bool OnCheckRoundFinish();
	virtual void OnRoundTimeOut();
	virtual bool RoundCount();
	virtual void OnGameKill(const MUID& uidAttacker, const MUID& uidVictim);

public:
	MMatchRuleTeamDeath2(MMatchStage* pStage);
	virtual ~MMatchRuleTeamDeath2()				{}
	virtual void CalcTeamBonus(MMatchObject* pAttacker, MMatchObject* pVictim,
		int nSrcExp, int* poutAttackerExp, int* poutTeamExp);
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_DEATHMATCH_TEAM2; }
};


class MMatchRuleTeamCTF : public MMatchRule {

private:
	MUID		m_uidRedFlagHolder;
	MUID		m_uidBlueFlagHolder;
	bool		m_bIsRedFlagTaken;
	bool		m_bIsBlueFlagTaken;
	MVector		m_BlueFlagPosition;
	MVector		m_RedFlagPosition;
private:
	inline void SetBlueFlagObtained(int state) { m_bIsBlueFlagTaken = state; }
	inline void SetRedFlagObtained(int state) { m_bIsRedFlagTaken = state; }
	inline void SetBlueCarrier(MUID state) { m_uidBlueFlagHolder = state; }
	inline void SetRedCarrier(MUID state) { m_uidRedFlagHolder = state; }
protected:
	//bool GetAliveCount(int* pRedAliveCount, int* pBlueAliveCount);
	void GetTeamScore(int* pRedTeamScore, int* pBLueTeamScore);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual bool OnRun();
	virtual void OnRoundBegin();
	virtual void OnRoundEnd();
	virtual void OnLeaveBattle(MUID& uidChar);
	virtual void OnEnterBattle(MUID& uidChar);
	virtual bool OnCheckRoundFinish();
	virtual void OnRoundTimeOut();
	virtual void RouteAssignFlag(MUID& uidBearer, int nTeam);
	virtual void RouteAssignFlagToJoiner(MUID& uidFlagBearer, MUID& uidSendTo, int nTeam);
	virtual void RouteAssignCap(int nTeam);
	virtual bool RoundCount();
	virtual void OnGameKill(const MUID& uidAttacker, const MUID& uidVictim);
	int nRedCount;
	int nBlueCount;
public:
	MMatchRuleTeamCTF(MMatchStage* pStage);
	virtual ~MMatchRuleTeamCTF()				{}
	virtual void CalcTeamBonus(MMatchObject* pAttacker, MMatchObject* pVictim,
								int nSrcExp, int* poutAttackerExp, int* poutTeamExp);
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_CTF; }
	virtual void OnObtainWorldItem(MMatchObject* pObj, int nItemID, int* pnExtraValues);
	inline MUID GetBlueCarrier() { return m_uidBlueFlagHolder; }
	inline MUID GetRedCarrier() { return m_uidRedFlagHolder; }

	inline MVector GetBlueFlagPosition() { return m_BlueFlagPosition; }
	inline MVector GetRedFlagPosition() { return m_RedFlagPosition; }
	inline void SetBlueFlagPosition(MVector &pos) { m_BlueFlagPosition = pos; }
	inline void SetRedFlagPosition(MVector &pos) { m_RedFlagPosition = pos; }
	inline bool IsBlueFlagTaken() { return m_bIsBlueFlagTaken; }
	inline bool IsRedFlagTaken() { return m_bIsRedFlagTaken; }
	virtual void RouteAssignState(MUID uidSendTo);
	virtual void SendAssignState();
};

/**********************************************

Paintball Team and Paintball Solo

**********************************************/

class MMatchRuleSoloPaintball : public MMatchRuleSoloDeath  {
public:
	MMatchRuleSoloPaintball(MMatchStage* pStage);
	virtual ~MMatchRuleSoloPaintball() { }
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_CLASSIC_SOLO; }
};

///////////////////////////////////////////////////////////////////////////////////////////////
class MMatchRuleTeamPaintball : public MMatchRuleTeamDeath {
public:
	MMatchRuleTeamPaintball(MMatchStage* pStage);
	virtual ~MMatchRuleTeamPaintball()				{}
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_CLASSIC_TEAM; }
};

class MMatchRuleModeStaff : public MMatchRule {
protected:
	bool CheckKillCount(MMatchObject* pOutObject);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual void OnRoundTimeOut();
	virtual bool OnCheckRoundFinish();
	virtual bool RoundCount();
public:
	MMatchRuleModeStaff(MMatchStage* pStage);
	virtual ~MMatchRuleModeStaff() { }
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_MODE_STAFF; }
};
#ifdef _GUNGAME
class MMatchRuleGunMode : public MMatchRule {
protected:
	bool CheckKillCount(MMatchObject* pOutObject);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual void OnRoundTimeOut();
	virtual bool OnCheckRoundFinish();
	virtual bool RoundCount();
public:
	MMatchRuleGunMode(MMatchStage* pStage);
	virtual ~MMatchRuleGunMode() { }
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_GUNMODE; }
};
#endif
//////////Zombie///////////////
class MMatchRuleTeamInfected : public MMatchRule
{
private:
	bool m_bInfectionStarted;
	const MUID ChooseInfected();
	MUID m_uidPatientZero;
	list<MUID> m_uidSurvivors;
	//list<int> m_PickHistory;

protected:
	bool GetAliveCount(int* pRedAliveCount, int* pBlueAliveCount);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual bool OnRun();
	void SetInfectedRoundState(MMATCH_ROUNDSTATE nState);
	//void OnPreCountDown();
	virtual void OnRoundBegin();
	virtual void OnRoundEnd();
	virtual void OnEnterBattle(MUID& uidChar);
	virtual void OnLeaveBattle(MUID& uidChar);
	virtual bool OnCheckRoundFinish();
	virtual void OnRoundTimeOut();
	virtual bool RoundCount();
	virtual bool OnCheckEnableBattleCondition();
	virtual void OnGameKill(const MUID& uidAttacker, const MUID& uidVictim);
	virtual void OnCommand(MCommand* pCommand);
	void OnInfectPlayer(const MUID& uidInfector, const MUID& uidVictim);

public:
	MMatchRuleTeamInfected(MMatchStage* pStage);
	virtual ~MMatchRuleTeamInfected()				{}
	virtual void CalcTeamBonus(MMatchObject* pAttacker, MMatchObject* pVictim,
		int nSrcExp, int* poutAttackerExp, int* poutTeamExp);
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_INFECTED; }
	virtual void* CreateRuleInfoBlob();
};
/////////////Zombie////////////////END//////
#endif