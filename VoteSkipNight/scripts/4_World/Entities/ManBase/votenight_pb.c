//Class that are modded to be overridden!
modded class PlayerBase extends ManBase
{	
	const float Vote_Night_WarnInterval = 10;
	protected float m_VoteNightTimer = 0.0;

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
				}
				
				if ( result == "fail" )
				{
					this.Message("[ VoteNight ] Vote was unsuccessful!", "colorAction");
				}
			}											
		}

		if ( GetGame().IsServer() )
		{
			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_VOTE)
			{								
				int desired_id = VoteSkipNight.VotePool.Find( sender.GetId() );
				if ( !VoteSkipNight.VotePool.Get( desired_id ) && GetGame().GetWorld().IsNight() )
				{
					if ( !VoteSkipNight.m_HasVoteEnded )
					{
						VoteSkipNight.VotePool.Insert( sender.GetId() );
						
						VoteSkipNight.UpdatePlayerCount();
						VoteSkipNight.CalculateVoteWinner();
					}
				}
			}											
		}
	}
}