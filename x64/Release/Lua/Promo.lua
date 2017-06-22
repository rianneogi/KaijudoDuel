package.path = package.path .. ';./?.lua;'
require("BaseSet")

Cards["Amnis, Holy Elemental"] = {
    name = "Amnis, Holy Elemental",
    set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Angel Command",
	cost = 7,

	shieldtrigger = 0,
	blocker = 1,

	power = 5000,
	breaker = 1,

    HandleMessage = function(id)
        if(getMessageType()=="get creaturecanblock") then
		    if(getMessageInt("blocker")==id) then
                if(getCardCiv(getMessageInt("attacker"))~=CIV_DARKNESS) then
			        setMessageInt("canblock",0)
                end
		    end
	    end
        local mod = function(cid,mid)
            if(getMessageType()=="mod creaturedestroy") then
		        if(getMessageInt("creature")==cid and getCardZone(cid)==ZONE_BATTLE) then
			        setMessageInt("msgContinue",0)
                    destroyModifier(cid,mid)
		        end
	        end
        end
        if(getMessageType()=="pre creaturebattle") then
		    if((getMessageInt("attacker")==id and getCardCiv(getMessageInt("defender"))==CIV_DARKNESS) or (getMessageInt("defender")==id and getCardCiv(getMessageInt("attacker"))==CIV_DARKNESS)) then
			    if(getCardZone(id)==ZONE_BATTLE) then
				    createModifier(id,mod)
			    end
		    end
	    end
    end
}

Cards["Armored Groblav"] = {
	name = "Armored Groblav",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.Evolution(id,"Human")
	    if(getMessageType()=="get creaturepower") then
		    if(getMessageInt("creature")==id and getAttacker()==id) then
                local size = getZoneSize(player,ZONE_BATTLE)
                local count = 0
                for i=0,(size-1) do
                    local sid = getCardAt(player,ZONE_BATTLE,i)
                    if(getCardType(sid)==TYPE_CREATURE and getCardCiv(sid)==CIV_FIRE and id~=sid) then
                        count = count+1
                    end
                end
                size = getZoneSize(getOpponent(player),ZONE_BATTLE)
                for i=0,(size-1) do
                    local sid = getCardAt(getOpponent(player),ZONE_BATTLE,i)
                    if(getCardType(sid)==TYPE_CREATURE and getCardCiv(sid)==CIV_FIRE and id~=sid) then
                        count = count+1
                    end
                end
			    setMessageInt("power",getMessageInt("power")+(count*1000))
		    end
        end
	end
}

Cards["Gigagrax"] = {
	name = "Gigagrax",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
	    if(getMessageType()=="post creaturedestroy") then
		    if(getMessageInt("creature")==id) then
                local ch = createChoice("Destroy an opponent's creature",1,id,getCardOwner(id),Checks.InOppBattle)
                if(ch>=0) then
                    destroyCard(ch)
                end
		    end
        end
	end
}

Cards["Loth Rix, the Iridescent"] = {
	name = "Loth Rix, the Iridescent",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.Evolution(id,"Guardian")
	    local func = function(id)
            Functions.moveTopCardsFromDeck(getCardOwner(id),ZONE_SHIELD,1)
        end
        Abils.onSummon(id,func)
	end
}

Cards["Neve, the Leveler"] = {
	name = "Neve, the Leveler",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Snow Faerie",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 2,

	HandleMessage = function(id)
	    local func = function(id)
            local owner = getCardOwner(id)
            local c1 = Functions.countCreaturesInBattle(owner)
            local c2 = Functions.countCreaturesInBattle(getOpponent(owner))
            if(c2>c1) then
                openDeck(owner)
                for i=1,(c2-c1) do
                    local ch = createChoice("Choose a creature in your deck",1,id,owner,Checks.CreatureInYourDeck)
	                if(ch>=0) then
                        moveCard(ch,ZONE_HAND)
                        shuffleDeck(getCardOwner(ch))
                    end
                    if(ch==RETURN_BUTTON1 or ch==RETURN_NOVALID) then
                        break
                    end
                end
                closeDeck(owner)
            end
        end
        Abils.onSummon(id,func)
	end
}

Cards["Olgate, Nightmare Samurai"] = {
	name = "Olgate, Nightmare Samurai",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
	    if(getMessageType()=="post creaturedestroy") then
            if(getCardOwner(id)==getCardOwner(getMessageInt("creature")) and getCardZone(id)==ZONE_BATTLE and isCardTapped(id)==1 and getMessageInt("creature")~=id) then
                local ch = createChoiceNoCheck("Untap this creature?",2,id,getCardOwner(id),Checks.False)
			    if(ch==RETURN_BUTTON1) then
                    untapCard(id)
                end
            end
        end
	end
}

Cards["Star-Cry Dragon"] = {
	name = "Star-Cry Dragon",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

	HandleMessage = function(id)
	    if(getMessageType()=="get creaturepower") then
            local cid = getMessageInt("creature")
            if(getCardOwner(id)==getCardOwner(cid) and isCreatureOfRace(cid,"Armored Dragon")==1 and getCardZone(cid)==ZONE_BATTLE) then
                Abils.bonusPower(cid,3000)
            end
        end
	end
}

Cards["Twister Fish"] = {
	name = "Twister Fish",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 5,

	shieldtrigger = 1,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Velyrika Dragon"] = {
	name = "Velyrika Dragon",
	set = "Promo",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
        local func = function(id)
            local func2 = function(cid,sid)
                if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_DECK and getCardType(sid)==TYPE_CREATURE and isCreatureOfRace(sid,"Armored Dragon")==1) then
		            return 1
	            else
		            return 0
	            end
            end
            local owner = getCardOwner(id)
            openDeck(owner)
	        local ch = createChoice("Choose a creature in your deck",0,id,owner,func2)
            closeDeck(owner)
	        if(ch>=0) then
                moveCard(ch,ZONE_HAND)
                shuffleDeck(getCardOwner(ch))
            end
        end
        Abils.onSummon(id,func)
	end
}