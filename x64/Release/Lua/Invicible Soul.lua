Cards["Craze Valkyrie, the Drastic"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id) --test
		Abils.Evolution(id,"Initiate")
		local func = function(id)
			local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
            if(ch>=0) then
                tapCard(ch)
				local ch2 = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
				if(ch2>=0) then
					tapCard(ch2)
				end
            end
		end
		Abils.onSummon(id, func)
	end
}

Cards["Ultra Mantis, Scourge of Fate"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.Evolution(id,"Giant Insect")
		Abils.cantBeBlockedPower(id,8000)
	end
}

Cards["Laveil, Seeker of Catastrophe"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 2,

	HandleMessage = function(id)
		Abils.untapAtEOT(id)
	end
}

Cards["Crystal Jouster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.Evolution(id,"Liquid People")
		Abils.returnAfterDestroyed(id)
	end
}

Cards["Q-tronic Hypermind"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.Evolution(id, "Survivor")
		local func = function(id)
			local owner = getCardOwner(id)
			local c = Functions.countInZone(owner,ZONE_BATTLE,Checks.IsSurvivor)
			drawCards(owner, c)
		end
		Abils.onSummon(id, func)
	end
}

Cards["Daidalos, General of Fury"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Phantasmal Horror Gigazald"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Bolmeteus Steel Dragon"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Lava Walker Executo"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cliffcrush Giant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Invincible Aura"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		Functions.moveTopCardsFromDeck(getCardOwner(id), ZONE_SHIELD, 3)
		Functions.EndSpell(id)
	end
}

Cards["Lu Gila, Silver Rift Guardian"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
		if(getMessageType()=="post cardmove") then
			local evo = getMessageInt("card")
			if(getCreatureIsEvolution(evo)==1 and getMessageInt("to")==ZONE_BATTLE) then
				tapCard(evo)
			end
		end
	end
}

Cards["Aeropica"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Invincible Technology"] = {
	shieldtrigger = 0,

	OnCast = function(id) --test
		local owner = getCardOwner(id)
        openDeck(owner)
		while(true) do
			local ch = createChoice("Choose a card in your deck",1,id,owner,Checks.InYourDeck)
			if(ch>=0) then
				moveCard(ch,ZONE_HAND)
			end
			if(ch<0) then
				break
			end
		end
		shuffleDeck(owner)
        closeDeck(owner)
        Functions.EndSpell(id)
	end
}

Cards["Invincible Abyss"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local func = function(cid,sid)
			destroyCreature(sid)
		end
		Functions.executeForCreaturesInBattle(id, getOpponent(getCardOwner(id)), func)
		Functions.EndSpell(id)
	end
}

Cards["Tank Mutant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Invincible Cataclysm"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch = createChoice("Choose an opponent's shield", 1, id, getCardOwner(id), Checks.InOppShields)
		if(ch>=0) then
			moveCard(ch, ZONE_GRAVEYARD)

			local ch2 = createChoice("Choose an opponent's shield", 1, id, getCardOwner(id), Checks.InOppShields)
			if(ch2>=0) then
				moveCard(ch, ZONE_GRAVEYARD)

				local ch3 = createChoice("Choose an opponent's shield", 1, id, getCardOwner(id), Checks.InOppShields)
				if(ch3>=0) then
					moveCard(ch, ZONE_GRAVEYARD)
				end
			end
		end
		Functions.EndSpell(id)
	end
}

Cards["Valiant Warrior Exorious"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.canAttackUntappedCreatures(id)
		Abils.PowerAttacker(id,3000)
	end
}

Cards["Invincible Unity"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local mod = function(cid,mid)
            Abils.PowerAttacker(cid,8000)
			Abils.Breaker(cid,3)
		    Abils.destroyModAtEOT(cid,mid)
        end
        local func = function(cid,sid)
            createModifier(sid,mod)
        end
		Functions.executeForCreaturesInBattle(id,getCardOwner(id),func)
        Functions.EndSpell(id)
	end
}

Cards["Splinterclaw Wasp"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Adomis, the Oracle"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Arc Bine, the Astounding"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Ballas, Vizier of Electrons"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Bonds of Justice"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Chekicul, Vizier of Endurance"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Chen Treg, Vizier of Blades"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cosmogold, Spectral Knight"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Dava Torey, Seeker of Clouds"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Forbos, Sanctum Guardian Q"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Gariel, Elemental of Sunbeams"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kanesill, the Explorer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Lightning Grass"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Moontear, Spectral Knight"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Protective Force"] = {
	shieldtrigger = 1,

	OnCast = function(id)
		local mod = function(cid,mid)
			Abils.bonusPower(cid, 4000)
			Abils.destroyModAtEOT(cid,mid)
		end
		
		local ch = createChoice("Choose a blocker", 0, id, getCardOwner(id), Checks.BlockerInYourBattle)
		if(ch>=0) then
			createModifier(ch, mod)
		end
		Functions.EndSpell(id)
	end
}

Cards["Rain of Arrows"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Razorpine Tree"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --test
		if(getMessageType()=="get creaturepower") then
			if(getMessageInt("creature")==id) then
				local c = Functions.countInZone(id,getCardOwner(id),ZONE_SHIELD,Checks.True)
				setMessageInt("power",getMessageInt("power")+c*2000)
			end
		end
	end
}

Cards["Sphere of Wonder"] = {
	shieldtrigger = 0,

	OnCast = function(id) --test
		local owner = getCardOwner(id)
        local c1 = getZoneSize(owner, ZONE_SHIELD)
        local c2 = getZoneSize(getOpponent(owner), ZONE_SHIELD)
        if(c2>c1) then
            Functions.moveTopCardsFromDeck(owner,ZONE_SHIELD,1)
        end
        Functions.EndSpell(id)
	end
}

Cards["Telitol, the Explorer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Vess, the Oracle"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Yuluk, the Oracle"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Rider"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Energy Stream"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		drawCards(getCardOwner(id), 2)
		Functions.EndSpell(id)
	end
}

Cards["Fort Megacluster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Hazard Crawler"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["King Triumphant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kyuroro"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Madrillon Fish"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
	end
}

Cards["Midnight Crawler"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Mystic Dreamscape"] = {
	shieldtrigger = 1,

	OnCast = function(id)
		local ch = createChoice("Choose a card in your mana zone",1,id,getCardOwner(id),Checks.InYourMana)
        if(ch>=0) then
			moveCard(ZONE_HAND)
			
			local ch2 = createChoice("Choose a card in your mana zone",1,id,getCardOwner(id),Checks.InYourMana)
			if(ch2>=0) then
				moveCard(ZONE_HAND)

				local ch3 = createChoice("Choose a card in your mana zone",1,id,getCardOwner(id),Checks.InYourMana)
				if(ch3>=0) then
					moveCard(ZONE_HAND)
				end
			end
        end
		Functions.EndSpell(id)
	end
}

Cards["Neon Cluster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Overload Cluster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Promephius Q"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Raptor Fish"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --test
		local summon = function(id)
			local func = function(cid,sid)
				moveCard(sid,ZONE_DECK)
			end
			local owner = getCardOwner(id)
			local c = getZoneSize(owner, ZONE_HAND)
			Functions.executeForCardsInZone(owner,ZONE_HAND,func)
			shuffleDeck(owner)
			drawCards(owner, c)
		end
		Abils.onSummon(id,summon)
	end
}

Cards["Ripple Lotus Q"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			local summon = function(id)
				local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
				if(ch>=0) then
					tapCard(ch)
				end
			end
			Abils.onSummon(id,summon)
		end
		Abils.Survivor(id,func)
	end
}

Cards["Shock Hurricane"] = {
	shieldtrigger = 0,

	OnCast = function(id) --test
		local count = 0
		while (true) do
			local ch = createChoice("Choose a creature in your battlezone", 1, id, getCardOwner(id), Checks.InYourBattle)
			if(ch>=0) then
				moveCard(ch,ZONE_HAND)
				count = count+1
			end
			if(ch<0) then
				break
			end
		end

		for i=1,count do
			local ch = createChoice("Choose a creature in your opponent's battlezone", 1, id, getCardOwner(id), Checks.InOppBattle)
			if(ch>=0) then
				moveCard(ch,ZONE_HAND)
			end
			if(ch<0) then
				break
			end
		end
	end
}

Cards["Sopian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Spiral Gate"] = {
	shieldtrigger = 1,

	OnCast = function(id)
        local ch = createChoice("Choose a creature",0,id,getCardOwner(id),Checks.InBattle)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
        Functions.EndSpell(id)
	end
}

Cards["Steam Star"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Thrash Crawler"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)

		local func = function(id)
			local ch = createChoice("Choose a card in your mana zone", 0, id, getCardOwner(id), Checks.InYourMana)
			if(ch>=0) then
				moveCard(ch, ZONE_HAND)
			end
		end
		Abils.onSummon(id,func)
	end
}

Cards["Zepimeteus"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
	end
}

Cards["Bazooka Mutant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --test
		Abils.cantAttackPlayers(id)
		if(getMessageType()=="get creaturecanattackcreature") then
			if(getMessageInt("attacker")==id and getCreatureIsBlocker(getMessageInt("defender"))==0) then
				setMessageInt("canattack",CANATTACK_NO)
			end
		end
	end
}

Cards["Cursed Pincher"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
		Abils.Slayer(id)
	end
}

Cards["Death Smoke"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),Checks.UntappedInOppBattle)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Functions.EndSpell(id)
	end
}

Cards["Frost Specter, Shadow of Age"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Hell Slash"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Gigagriff"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.Slayer(id)
		Abils.cantAttack(id)
	end
}

Cards["Gnarvash, Merchant of Blood"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Grave Worm Q"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Grim Soul, Shadow of Reversal"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Grinning Axe, the Monstrosity"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.Slayer(id)
	end
}

Cards["Wicked Soul Reincarnation"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Junkatz, Rabid Doll"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Lone Tear, Shadow of Solitude"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="pre endturn") then
			if(getMessageInt("player")==getCardOwner(id) and getCardZone(id)==ZONE_BATTLE) then
				local c = Functions.countInZone(getCardOwner(id), ZONE_BATTLE, Checks.True)
				if(c<=1) then
					destroyCreature(id)
				end
			end
		end
	end
}

Cards["Lupa, Poison-Tipped Doll"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Proclamation of Death"] = {
	shieldtrigger = 1,

	OnCast = function(id)
		local ch = createChoice("Choose a creature in your battlezone",0,id,getOpponet(getCardOwner(id)),Checks.InOppBattle)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Functions.EndSpell(id)
	end
}

Cards["Schuka, Duke of Amnesia"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local summon = function(id)
			local func = function(cid,sid)
				moveCard(sid,ZONE_GRAVEYARD)
			end
			local owner = getCardOwner(id)
			Functions.executeForCardsInZone(owner, ZONE_HAND, func)
			Functions.executeForCardsInZone(getOpponent(owner), ZONE_HAND, func)
		end
		Abils.onDestroy(id,summon)
	end
}

Cards["Skullcutter, Swarm Leader"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --test
		if(getMessageType()=="pre endturn") then
			if(getMessageInt("player")==getCardOwner(id) and getCardZone(id)==ZONE_BATTLE) then
				local c = Functions.countInZone(getCardOwner(id), ZONE_BATTLE, Checks.True)
				if(c<=1) then
					destroyCreature(id)
				end
			end
		end
	end
}

Cards["Tentacle Worm"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Vile Mulder, Wing of the Void"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.destroyAfterBattle(id)
		Abils.cantAttackCreatures(id)
	end
}

Cards["Zorvaz, the Bonecrusher"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.destroyAfterBattle(id)
		Abils.cantAttack(id)
	end
}

Cards["Armored Decimator Valkaizer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Armored Scout Gestuchar"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Automated Weaponmaster Machai"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.attacksEachTurn(id)
	end
}

Cards["Badlands Lizard"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Bazagazeal Dragon"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id) --test
		Abils.returnAtEOT(id)
		Abils.SpeedAttacker(id)
		Abils.canAttackUntappedCreatures(id)
	end
}

Cards["Choya, the Unheeding"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cocco Lupia"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Comet Missile"] = {
	shieldtrigger = 1,

	OnCast = function(id) --test
		local check = function(cid,sid)
			if(getCardType(sid)==TYPE_CREATURE and getCreaturePower(sid)<=6000) then
				return Checks.BlockerInOppBattle(cid,sid)
			else
				return 0
			end
		end
		
		local ch = createChoice("Choose an opponent's blocker",1,id,getCardOwner(id),check)
		if(ch>=0) then
			destroyCreature(ch)
		end
	end
}

Cards["Crisis Boulder"] = {
	shieldtrigger = 1,

	OnCast = function(id) --test
		local check = function(cid,sid)
			return (Checks.InOppMana(cid,sid) or Checks.InOppBattle(cid,sid))
		end
		
		local ch = createChoice("Choose an card in your battle zone or mana zone",0,id,getOpponent(getCardOwner(id)),check)
		if(ch>=0) then
			if(getCardZone(ch)==ZONE_BATTLE) then
				destroyCreature(ch)
			end
			if(getCardZone(ch)==ZONE_MANA) then
				destroyMana(ch)
			end
		end
	end
}

Cards["Cutthroat Skyterror"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --test
		Abils.cantAttackPlayers(id)
		Abils.SpeedAttacker(id)
		Abils.returnAtEOT(id)
	end
}

Cards["Legionnaire Lizard"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Migasa, Adept of Chaos"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Phantom Dragon's Flame"] = {
	shieldtrigger = 1,

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
	end
}

Cards["Picora's Wrench"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Pyrofighter Magnus"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.returnAtEOT(id)
		Abils.SpeedAttacker(id)
	end
}

Cards["Q-tronic Gargantua"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Rikabu's Screwdriver"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Rumblesaur Q"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			Abils.SpeedAttacker(id)
		end
		Abils.Survivor(id,func)
	end
}

Cards["Spastic Missile"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local valid = function(cid,sid)
            if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCreaturePower(sid)<=3000) then
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
	end
}

Cards["Torchclencher"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Bliss Totem, Avatar of Luck"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cantankerous Giant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Carrier Shell"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Charmilia, the Enticer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Clobber Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
		Abils.cantBeBlockedPower(id,5000)
	end
}

Cards["Dimension Gate"] = {
	shieldtrigger = 1,

	OnCast = function(id)
		local owner = getCardOwner(id)
        openDeck(owner)
	    local ch = createChoice("Choose a creature in your deck",0,id,owner,Checks.CreatureInYourDeck)
        closeDeck(owner)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
		shuffleDeck(owner)
        Functions.EndSpell(id)
	end
}

Cards["Factory Shell Q"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			local summon = function(id)
				local owner = getCardOwner(id)
				openDeck(owner)
				local ch = createChoice("Choose a creature in your deck",0,id,owner,Checks.SurvivorInYourDeck)
				closeDeck(owner)
				if(ch>=0) then
					moveCard(ch,ZONE_HAND)
				end
				shuffleDeck(owner)
			end
			Abils.onSummon(id,summon)
		end
		Abils.Survivor(id,func)
	end
}

Cards["Faerie Life"] = {
	shieldtrigger = 1,

	OnCast = function(id)
		Functions.moveTopCardsFromDeck(getCardOwner(id), ZONE_MANA, 1)
		Functions.EndSpell(id)
	end
}

Cards["Feather Horn, the Tracker"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Forbidding Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Garabon, the Glider"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Illusory Berry"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Innocent Hunter, Blade of All"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Living Citadel Vosh"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Mighty Bandit, Ace of Thieves"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Mystic Treasure Chest"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Pangaea's Will"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Paradise Horn"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Slumber Shell"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Trench Scarab"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
		Abils.PowerAttacker(id,4000)
	end
}

