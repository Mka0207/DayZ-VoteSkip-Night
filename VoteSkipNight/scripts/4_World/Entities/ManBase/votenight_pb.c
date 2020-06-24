//Class that are modded to be overridden!
modded class PlayerBase extends ManBase
{	
	const float Vote_Night_WarnInterval = 10;
	protected float m_VoteNightTimer = 0.0;

	static autoptr ref set<string> VotePool;

	override void Init()
	{
		super.Init();
		if ( GetGame().IsClient() )
		{
			if ( VotePool.Count() <= 0 ) 
			{
				VotePool = new set<string>;
			}
		}
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);	
			
		if ( GetGame().IsClient() )
		{
			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_NOTIFY)
			{								
				string result;
				ctx.Read(result);

				if ( result == "win" )
				{
					this.Message("[ VoteNight ] Vote was successful! Skipping night...", "colorAction");

					VotePool.Clear();
				}
			}

			/*if (rpc_type == VOTE_NIGHT.SKIPNIGHT_NOTIFY_FAIL)
			{
				int votes_in_pool;
				int votes_remaning_till_win;
				ctx.Read(votes_in_pool);
				ctx.Read(votes_remaning_till_win);

				this.Message("[ VoteNight ] "+votes_in_pool+"/"+votes_remaning_till_win+" votes remaining until daylight is forced", "colorAction");
			}*/

			/*if (rpc_type == VOTE_NIGHT.SKIPNIGHT_SYNC_VOTEPOOL)
			{
				string voter_id;
				ctx.Read(voter_id);
				VotePool.Insert(voter_id);
			}*/						
		}

		if ( GetGame().IsServer() )
		{
			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_VOTE)
			{								
				int desired_id = VoteSkipNight.VotePool.Find( sender.GetId() );
				if ( !VoteSkipNight.VotePool.Get( desired_id ) )
				{
					if ( GetGame().GetWorld().IsNight() )
					{
						if ( !VoteSkipNight.m_HasVoteEnded )
						{
							VoteSkipNight.VotePool.Insert( sender.GetId() );
							//VoteSkipNight.SyncVoteData();
							
							VoteSkipNight.UpdatePlayerCount();
							VoteSkipNight.CalculateVoteWinner();
						}
					}
				}
				else
				{
					Param1<string> warn;
					warn = new Param1<string>( "[ VoteNight ] Error! duplicate vote canceled." );
					this.RPCSingleParam( ERPCs.RPC_USER_ACTION_MESSAGE, warn, true, this.GetIdentity() );
				}
				
			}											
		}
	}
}