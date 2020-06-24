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
					ScriptRPC rpc = new ScriptRPC();
					rpc.Send(GetGame().GetPlayer(), VOTE_NIGHT.SKIPNIGHT_VOTE, true, GetGame().GetPlayer().GetIdentity());
					GetGame().Chat("[ VoteNight ] You have voted to skip night!", "colorAction");
				}
				else
				{
					ScriptRPC rpc2 = new ScriptRPC();
					rpc2.Send(GetGame().GetPlayer(), VOTE_NIGHT.SKIPNIGHT_VOTE, true, GetGame().GetPlayer().GetIdentity());
					GetGame().Chat("[ VoteNight ] Cannot vote, it isn't Night yet!", "colorAction");
				}
				
			}
		}

		return true;
	}
}