class CfgPatches
{
	class VoteSkipNight
	{
		requiredAddons[]=
		{
			//""
		};
	};
};

class CfgMods
{
	class VoteSkipNight
	{
		dir="VoteSkipNight";
		name="VoteSkipNight";
		credits="Mka0207";
		author="Mka0207";
	    type = "mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		
	    class defs
	    {
			class gameScriptModule
            {
                value="";
                files[]={"VoteSkipNight/scripts/3_Game"};
            };
			
            class worldScriptModule
            {
                value="";
                files[]={"VoteSkipNight/scripts/4_World"};
            };
             
			
            class missionScriptModule
            {
                value="";
                files[]={"VoteSkipNight/scripts/5_Mission"};
            };
        };
    };
};