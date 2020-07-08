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

			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_NOTIFY_FAIL)
			{								
				this.Message("[ VoteNight ] Error! duplicate vote canceled.", "colorAction");
			}

			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_SYNC_VOTEPOOL)
			{
				int votes_left = 0;
				ctx.Read(votes_left);

				if ( votes_left > 0 )
				{	
					this.Message("[ VoteNight ] "+votes_left+" votes until Night is forced.", "colorAction");
				}
			}
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
							VoteSkipNight.UpdatePlayerCount();
							VoteSkipNight.CalculateVoteWinner();

							int RequiredVotes = Math.Ceil( VoteSkipNight.CurrentNumOfPlys * 0.5 );
							int CurrentNumVotes = VoteSkipNight.VotePool.Count();
							int diff = RequiredVotes-CurrentNumVotes;

							Print( RequiredVotes );
							Print( CurrentNumVotes );
							Print( diff );

							ScriptRPC rpc2 = new ScriptRPC();
							rpc2.Write(diff);
							rpc2.Send( this, VOTE_NIGHT.SKIPNIGHT_SYNC_VOTEPOOL, true, this.GetIdentity()) ;

							//this.RPCSingleParam( VOTE_NIGHT.SKIPNIGHT_SYNC_VOTEPOOL, new Param1<int>( 0 ), true, this.GetIdentity() );
						}
					}
				}
				else
				{
					Param1<string> warn;
					warn = new Param1<string>( "" );
					this.RPCSingleParam( VOTE_NIGHT.SKIPNIGHT_NOTIFY_FAIL, warn, true, this.GetIdentity() );
				}
			}											
		}
	}
}