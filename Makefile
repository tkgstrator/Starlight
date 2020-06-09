# TODO (Khangaroo): Make this process a lot less hacky (no, export did not work)
# See MakefileNSO

.PHONY: all clean starlight install 

S2VER ?= 310
S2VERSTR ?= 3.1.0
S2ROMTYPE ?= TrialUS20
IP ?= 192.168.0.15
all:
	@docker run --rm -v $(PWD):/home/starlight/Starlight -it tkgling/starlight

starlight:
	$(MAKE) clean -f MakefileNSO
	@rm -fr starlight_patch_*
	$(MAKE) all -f MakefileNSO S2VER=$(S2VER) S2VERSTR=$(S2VERSTR)
	$(MAKE) starlight_patch_$(S2VER)/*.ips

starlight_patch_$(S2VER)/*.ips: patches/*.slpatch patches/configs/$(S2VER).config patches/maps/$(S2VER)/*.map \
								build$(S2VER)/$(shell basename $(CURDIR))$(S2VER).map scripts/genPatch.py
	@rm -f starlight_patch_$(S2VER)/*.ips
	python3.7 scripts/genPatch.py $(S2VER)

install: all
	python3 scripts/sendPatch.py $(IP) $(S2ROMTYPE) $(S2VER)

clean:
	$(MAKE) clean -f MakefileNSO
	@rm -fr starlight_patch_*
