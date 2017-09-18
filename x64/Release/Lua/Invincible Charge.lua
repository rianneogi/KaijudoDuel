package.path = package.path .. ';./?.lua;'
require("Invincible Soul")

Cards["Siri, Glory Elemental"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cosmic Nebula"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Crath Lade, Merciless King"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Sky Crusher, the Agitator"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Headlong Giant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 3,

	HandleMessage = function(id) --todo
		Abils.cantBeBlockedPower(id, 4000)

		local func = function(id)
			discardCardAtRandom(getCardOwner(id))
		end
		Abils.onAttack(id,func)
		
		if(getMessageType()=="get creaturecanattackcreature") then
			if(getMessageInt("attacker")==id) then
				local s = getZoneSize(getCardOwner(id), ZONE_HAND)
				if(s==0) then
					setMessageInt("canattack",CANATTACK_NO)
				end
			end
		end
		if(getMessageType()=="get creaturecanattackplayers") then
			if(getMessageInt("attacker")==id) then
				local s = getZoneSize(getCardOwner(id), ZONE_HAND)
				if(s==0) then
					setMessageInt("canattack",CANATTACK_NO)
				end
			end
		end
	end
}

Cards["Gandar, Seeker of Explosions"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["King Benthos"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Battleship Mutant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Armored Transport Galiacruse"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Spinning Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Bex, the Oracle"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Geoshine, Spectral Knight"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Justice Jamming"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Kizar Basiku, the Outrageous"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 2,

	HandleMessage = function(id)
		Abils.Evolution(id,"Initiate")
		Abils.Stealth(id,CIV_FIRE)
	end
}

Cards["Lightning Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
        local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
        if(ch>=0) then
			tapCard(ch)
        end
        Functions.EndSpell(id)
	end,

    HandleMessage = function(id)
        Abils.Charger(id)
    end
}

Cards["Miracle Portal"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Pulsar Tree"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Rodi Gale, Night Guardian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.Stealth(id,CIV_DARKNESS)
	end
}

Cards["Rom, Vizier of Tendrils"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local summon = function(id)
            local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
            if(ch>=0) then
                tapCard(ch)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Rondobil, the Explorer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Agent"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Fencer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Biancus"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cetibols"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			drawCards(getCardOwner(id),count)
		end
		Abils.onDestroy(id,func)
	end
}

Cards["Curious Eye"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Garatyano"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Riptide Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch = createChoice("Choose a creature",0,id,getCardOwner(id),Checks.InBattle)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
        Functions.EndSpell(id)
	end,

	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Splash Zebrafish"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
            local ch = createChoice("Choose a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
            if(ch>=0) then
                moveCard(ZONE_HAND)
            end
        end
		Abils.onSummon(id,func)
		Abils.cantBeBlocked(id)
	end
}

Cards["Titanium Cluster"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeAttacked(id)
		Abils.cantAttack(id)
	end
}

Cards["Trenchdive Shark"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Dream Pirate, Shadow of Theft"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Gezary, Undercover Doll"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.Stealth(id,CIV_NATURE)
	end
}

Cards["Gigabuster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Hopeless Vortex"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),Checks.InOppBattle)
	    if(ch>=0) then
            destroyCreature(ch)
        end
	end
}

Cards["Phantasmal Horror Gigazabal"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.Evolution(id, "Chimera")
		Abils.Stealth(id, CIV_LIGHT)
	end
}

Cards["Propeller Mutant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			discardCardAtRandom(getOpponent(getCardOwner(id)))
		end
		Abils.onDestroy(id,func)
	end
}

Cards["Scalpel Spider"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Three-Faced Ashura Fang"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Vacuum Gel"] = { --test
	shieldtrigger = 1,

	OnCast = function(id)
		local check = function(cid,sid)
			if(Checks.UntappedInOppBattle(cid,sid)==1) then
				if(getCardCiv(sid)==CIV_NATURE or getCardCiv(sid)==CIV_LIGHT) then
					return 1
				else
					return 0
				end
			else
				return 0
			end
		end

		local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),check)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Functions.EndSpell(id)
	end
}

Cards["Venom Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Apocalypse Vise"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Astronaut Skyterror"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cratersaur"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Energy Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Gazarias Dragon"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kipo's Contraption"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kooc Pollon"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeAttacked(id)
	end
}

Cards["Otherworldly Warrior Naglu"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.cantBeAttacked(id)
		Abils.PowerAttacker(id,3000)
	end
}

Cards["Valkrowzer, Ultra Rock Beast"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.Evolution(id, "Rock Beast")
		Abils.Stealth(id, CIV_WATER)
	end
}

Cards["Wild Racer Chief Garan"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,1000)
		Abils.Stealth(id,CIV_LIGHT)
	end
}

Cards["Brood Shell"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cursed Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Freezing Icehammer"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Fruit of Eternity"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Launch Locust"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Mulch Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Popple, Flowerpetal Dancer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Stinger Horn, the Delver"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,1000)
		Abils.Stealth(id,CIV_WATER)
	end
}

Cards["Tangle Fist, the Weaver"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["World Tree, Root of Life"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.Evolution(id,"Tree Folk")
		Abils.PowerAttacker(id,2000)
		Abils.Stealth(id,CIV_DARKNESS)
	end
}

