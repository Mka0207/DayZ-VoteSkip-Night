class VoteSkipNight
{
	static autoptr ref set<string> VotePool = new set<string>;
	static int CurrentNumOfPlys = 0;
	static ref array<Man> CurrentArrayOfPlys = new array<Man>;
	static bool m_HasVoteEnded = false;

	void VoteSkipNight()
	{
	}
	void ~VoteSkipNight()
	{
	}

	static void UpdatePlayerCount()
	{
		GetGame().GetWorld().GetPlayerList(VoteSkipNight.CurrentArrayOfPlys);

		if ( VoteSkipNight.CurrentArrayOfPlys.Count() > 0 )
		{
			VoteSkipNight.CurrentNumOfPlys = VoteSkipNight.CurrentArrayOfPlys.Count();
		}
	}

	static void ResetVotingData()
	{
		VotePool.Clear();
		CurrentNumOfPlys = 0;
		CurrentArrayOfPlys.Clear();
		m_HasVoteEnded = false;

		//Print("Reset Data!");
	}

	static void AnnounceFail()
	{
		foreach ( Man player: CurrentArrayOfPlys )
		{
			PlayerBase m_Player;
			m_Player = PlayerBase.Cast(player);

			ScriptRPC rpc = new ScriptRPC();
			rpc.Write("fail");
			rpc.Send( m_Player, VOTE_NIGHT.SKIPNIGHT_NOTIFY, true, m_Player.GetIdentity()) ;
		}

		ResetVotingData();
	}

	static void AnnounceWin()
	{
		foreach ( Man player: CurrentArrayOfPlys )
		{
			PlayerBase m_Player;
			m_Player = PlayerBase.Cast(player);

			ScriptRPC rpc2 = new ScriptRPC();
			rpc2.Write("win");
			rpc2.Send( m_Player, VOTE_NIGHT.SKIPNIGHT_NOTIFY, true, m_Player.GetIdentity()) ;
		}

		//Set the time to day.
		int year, month, day, hour, minute;
		GetGame().GetWorld().GetDate(year, month, day, hour, minute);
		GetGame().GetWorld().SetDate(year, month, day, 10, minute);
		//Print("Time has been set to day light!");

		ResetVotingData();
	}

	static void CalculateVoteWinner()
	{
		if ( VotePool.Count() >= Math.Ceil( CurrentNumOfPlys * 0.75 ) )
		{
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( VoteSkipNight.AnnounceWin, 10000, false );
			m_HasVoteEnded = true;
		}
		else
		{
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( VoteSkipNight.AnnounceFail, 10000, false );
			m_HasVoteEnded = true;
		}
	}
}