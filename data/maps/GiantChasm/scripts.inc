GiantChasm_MapScripts::
	.byte 0

GiantChasm_EventScript_PreventExitSouth::
	lockall
	msgbox GiantChasm_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, GiantChasm_Movement_PreventExitSouth
	waitmovement 0
	releaseall
	end

GiantChasm_EventScript_PreventExitWest::
	lockall
	msgbox GiantChasm_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, GiantChasm_Movement_PreventExitWest
	waitmovement 0
	releaseall
	end

GiantChasm_EventScript_PreventExitNorth::
	lockall
	msgbox GiantChasm_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, GiantChasm_Movement_PreventExitNorth
	waitmovement 0
	releaseall
	end

GiantChasm_Movement_PreventExitSouth:
	walk_up
	step_end

GiantChasm_Movement_PreventExitWest:
	walk_left
	step_end

GiantChasm_Movement_PreventExitNorth:
	walk_down
	step_end

GiantChasm_EventScript_BirchsBag::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, GiantChasm_EventScript_Got_PKMN
	faceplayer
    setvar VAR_GIANT_CHASM_STATE, 1
	setflag FLAG_SYS_POKEMON_GET
	fadescreen FADE_TO_BLACK
	setobjectxy LOCALID_PLAYER, 15, 10
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special ChooseStarter
	waitstate
	release
	call Common_EventScript_NameReceivedPartyMon
	end

GiantChasm_EventScript_Got_PKMN::
 msgbox GiantChasm_Text_Run_Wild, MSGBOX_NPC
 end

GiantChasm_EventScript_Dead::
 msgbox GiantChasm_Text_DeaderTree, MSGBOX_NPC
 end

GiantChasm_EventScript_Birch::
        lock
        goto_if_set DN_FLAG_DEXNAV_GET, GiantChasm_EventScript_Dead
        msgbox GiantChasm_Text_DeadTree, MSGBOX_NPC
        giveitem ITEM_ESCAPE_ROPE 1
        giveitem ITEM_EXP_SHARE 5
        giveitem ITEM_OVAL_CHARM 1
        giveitem ITEM_SHINY_CHARM 1
        giveitem ITEM_CATCHING_CHARM 1
        giveitem ITEM_GLIMMERING_CHARM 1
        giveitem ITEM_EXP_CHARM 1
        giveitem ITEM_MEGA_RING 1
        giveitem ITEM_Z_POWER_RING 1
        giveitem ITEM_DYNAMAX_BAND 1
        giveitem ITEM_VS_SEEKER 1
        giveitem ITEM_POKEMON_BOX_LINK 1
        giveitem ITEM_BERRY_POUCH 1
        giveitem ITEM_POKE_RADAR 1
        giveitem ITEM_TERA_ORB 1
		setflag B_FLAG_TERA_ORB_NO_COST
        msgbox GiantChasm_Text_Pokedex, MSGBOX_DEFAULT
		setflag FLAG_SYS_POKEDEX_GET
		setflag FLAG_ADVENTURE_STARTED
		special SetUnlockedPokedexFlags
		Setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
		msgbox GiantChasm_Text_Dexnav, MSGBOX_DEFAULT
		setflag DN_FLAG_DEXNAV_GET 
		setflag FLAG_SYS_POKENAV_GET
		msgbox GiantChasm_Text_Pokenav, MSGBOX_DEFAULT
		giveitem ITEM_POKE_BALL 20
        release
	    end

GiantChasm_Text_DeadTree:
	.string "The Proffessor isn't moving\n"
	.string "He must have hit his head in the fall.\p"
	.string "Well he won't need theese anymore$"

GiantChasm_Text_DontLeaveMe:
	.string "I shouln't go yet\n"
	.string "there is still valuables here!$"

GiantChasm_Text_DeaderTree:
        .string "The Proffessor still isn't moving\n"
	    .string "Eh may as well leave him here.$"

GiantChasm_Text_Pokedex:
        .string "{PLAYER} recieved the POKEDEX!$"

GiantChasm_Text_Dexnav:
        .string "{PLAYER} recieved the DEXNAV!$"

GiantChasm_Text_Pokenav:
        .string "{PLAYER} recieved the POKENAV!$"

GiantChasm_Text_Run_Wild:
        .string "The other two pokemon escaped!$"
