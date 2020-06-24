modded class MissionServer extends MissionBase
{
		
	const float ADVERT_DELAY = 600;
	float AdCheckTimer = 0.0
	ref array<Man> GetPlys;

	override void OnInit()
	{
		super.OnInit();
		GetPlys = new array<Man>;
	}

	override void TickScheduler(float timeslice)
	{
		super.TickScheduler(timeslice);

		if ( GetGame().GetWorld().IsNight() )
		{
			AdCheckTimer += timeslice;

			if ( AdCheckTimer > ADVERT_DELAY )
			{
				GetGame().GetPlayers( GetPlys );

				foreach ( Man ply: GetPlys )
				{
					PlayerBase play;
					Class.CastTo(play, ply);
					if ( play )
					{
						Param1<string> params2;
						params2 = new Param1<string>( "[ VoteNight ] You can type /skip to advance to daytime." );
						play.RPCSingleParam( ERPCs.RPC_USER_ACTION_MESSAGE, params2, true, play.GetIdentity() );
					}
				}
				AdCheckTimer = 0.0;
			}
		}
	}
}