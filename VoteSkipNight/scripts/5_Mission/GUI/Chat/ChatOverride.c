modded class ChatInputMenu extends UIScriptedMenu
{
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		super.OnChange(w, x, y, finished);

		if (!finished) return false;

		if (m_edit_box.GetText() != "")
		{
			if ( m_edit_box.GetText() == "/skip" )
			{
				if ( GetGame().GetWorld().IsNight() )
				{
					/*PlayerBase m_Player;
					m_Player = PlayerBase.Cast( GetGame().GetPlayer() );
					int desired_id = m_Player.VotePool.Find( GetGame().GetPlayer().GetIdentity().GetId() );
					if ( VoteSkipNight.VotePool.Get( desired_id )
					{
						GetGame().Chat("[ VoteNight ] You have already voted!", "colorAction");
					}
					else
					{*/
						ScriptRPC rpc = new ScriptRPC();
						rpc.Send(GetGame().GetPlayer(), VOTE_NIGHT.SKIPNIGHT_VOTE, true, GetGame().GetPlayer().GetIdentity());
						GetGame().Chat("[ VoteNight ] You have submitted a vote.", "colorAction");
					//}
				}
				else
				{
					GetGame().Chat("[ VoteNight ] Cannot vote, it isn't Night yet!", "colorAction");
				}
				
			}
		}

		return true;
	}
}