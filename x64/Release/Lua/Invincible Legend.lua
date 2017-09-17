Cards["Nastasha, Channeler of Suns"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Emperor Quazla"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Super Necrodragon Abzo Dolba"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 3,

	HandleMessage = function(id)
		Abils.Evolution(id, "Dragon")

		if(getMessageType()=="get creaturepower") then
			if(getMessageInt("creature")==id) then
				local c = Functions.countInZone(id, getCardOwner(id), ZONE_GRAVEYARD, Checks.IsCreature)
				setMessageInt("power",getMessageInt("power")+c*2000)
			end
		end
	end
}

Cards["Uberdragon Bajula"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 3,

	HandleMessage = function(id)
		Abils.Evolution(id,"Dragon")
		Abils.destroyOppManaOnAttack(id,2)
	end
}

Cards["Super Terradragon Bailas Gale"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kuukai, Finder of Karma"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Ranger"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeBlocked(id)
		Abils.returnAfterDestroyed(id)
	end
}

Cards["Megaria, Empress of Dread"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Magmadragon Jagalzor"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kachua, Keeper of the Icegate"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Dracobarrier"] = {
	shieldtrigger = 1,

	OnCast = function(id)
		local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
        if(ch>=0) then
			tapCard(ch)

			if(isCreatureOfRace(ch,"Dragon")==1) then
				Functions.moveTopCardsFromDeck(getCardOwner(id), ZONE_SHIELD, 1)
			end
        end
	end
}

Cards["Laser Whip"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch1 = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
        if(ch1>=0) then
			tapCard(ch1)
        end
		
		local mod = function(cid,mid)
            Abils.cantBeBlocked(cid)
	        Abils.destroyModAtEOT(cid,mid)
        end

		local ch2 = createChoice("Choose a creature in your battlezone",1,id,getCardOwner(id),Checks.InYourBattle)
		if(ch2>=0) then
            createModifier(ch2,mod)
        end
        Functions.EndSpell(id)
	end
}

Cards["Lunar Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Migalo, Vizier of Spycraft"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Misha, Channeler of Suns"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Nariel, the Oracle"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Sasha, Channeler of Suns"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Sol Galla, Halo Guardian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Solar Grass"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Thrumiss, Zephyr Guardian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Grappler"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Candy Cluster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeBlocked(id)
	end
}

Cards["Eureka Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		drawCards(getCardOwner(id),1)
	end,
	
	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Grape Globbo"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Illusion Fish"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Lalicious"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Marine Scramble"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Prowling Elephish"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Vikorakys"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Wave Lance"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch = createChoice("Choose a creature",0,id,getCardOwner(id),Checks.InBattle)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)

			if(isCreatureOfRace(ch, "Dragon")==1) then
				drawCards(getCardOwner(id), 1)
			end
        end
        Functions.EndSpell(id)
	end
}

Cards["Corpse Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch = createChoice("Choose a creature in your graveyard",0,id,getCardOwner(id),Checks.CreatureInYourGraveyard)
        if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
        Functions.EndSpell(id)
	end,

	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Skeleton Vice"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Dimension Splitter"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Gachack, Mechanical Doll"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Gigaclaws"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Motorcycle Mutant"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)

		if(getMessageType()=="post cardmove") then
			if(getCardOwner(getMessageInt("card"))==getCardOwner(id) and getMessageInt("to")==ZONE_BATTLE) then
				destroyCreature(id)
			end
		end
	end
}

Cards["Necrodragon Galbazeek"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		local func = function(id)
			local ch = createChoice("Choose a shield", 0, id, getCardOwner(id), Checks.InYourShields)
			if(ch>=0) then
				moveCard(ch, ZONE_GRAVEYARD)
			end
		end

		Abils.onAttack(id,func)
	end
}

Cards["Necrodragon Giland"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Scream Slicer, Shadow of Fear"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Tyrant Worm"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="post cardmove") then
			if(getCardOwner(getMessageInt("card"))==getCardOwner(id) and getMessageInt("to")==ZONE_BATTLE) then
				destroyCreature(id)
			end
		end
	end
}

Cards["Bruiser Dragon"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			local ch = createChoice("Choose a shield", 0, id, getCardOwner(id), Checks.InYourShields)
			if(ch>=0) then
				moveCard(ch, ZONE_GRAVEYARD)
			end
		end
		Abils.onDestroy(id, func)
	end
}

Cards["Furious Onslaught"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Kyrstron, Lair Delver"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local check = function(cid,sid)
			if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_HAND and isCreatureOfRace(sid, "Dragon")==1) then
				return 1
			else
				return 0
			end
		end
		
		local func = function(id)
			local ch = createChoice("Choose a dragon in your hand", 0, id, getCardOwner(id), check)
			if(ch>=0) then
				moveCard(ch, ZONE_BATTLE)
			end
		end
		Abils.onDestroy(id,func)
	end
}

Cards["Magmadragon Melgars"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Missile Soldier Ultimo"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Rocketdive Skyterror"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeAttacked(id)
		Abils.cantAttackPlayers(id)
		Abils.PowerAttacker(id,1000)
	end
}

Cards["Slaphappy Soldier Galback"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Torpedo Skyterror"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Totto Pipicchi"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Volcano Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local valid = function(cid,sid)
            if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCreaturePower(sid)<=2000) then
		        return 1
	        else
		        return 0
	        end
        end
        local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),valid)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Functions.EndSpell(id)
	end,

	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Bakkra Horn, the Silent"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="post cardmove") then
			local summoned = getMessageInt("card")
			if(getCardOwner("summoned")==getCardOwner(id) and getMessageInt("to")==ZONE_BATTLE) then
				if(isCreatureOfRace(summoned, "Dragon")==id or isCreatureOfRace(summoned, "Dragonoid")==id) then
					Functions.moveTopCardsFromDeck(getCardOwner(id), ZONE_MANA, 1)
				end
			end
		end
	end
}

Cards["Carbonite Scarab"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Coliseum Shell"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Dracodance Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Muscle Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local mod = function(cid,mid)
            Abils.bonusPower(cid,3000)
		    Abils.destroyModAtEOT(cid,mid)
        end
        local func = function(cid,sid)
            createModifier(sid,mod)
        end
		Functions.executeForCreaturesInBattle(id,getCardOwner(id),func)
        Functions.EndSpell(id)
	end,

	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Quixotic Hero Swine Snout"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Root Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Senia, Orchard Avenger"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Terradragon Gamiratar"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		local check = function(cid,sid)
			if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_HAND and getCardType(sid)==TYPE_CREATURE) then
			return 1
		else
			return 0
		end

		local func = function(id)
			local ch = createChoice("Choose a creature in your hand", 1, id, getOpponent(getCardOwner(id)), check)
			if(ch>=0) then
				moveCard(ch, ZONE_BATTLE)
			end
		end

		Abils.onSummon(id, func)
	end
}

Cards["Terradragon Regarion"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,3000)
	end
}

