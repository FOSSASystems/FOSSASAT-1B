DOCKERUSER=fossasystems
DOCKERNAME=fossasat
DOCKERTAG=$(DOCKERUSER)/$(DOCKERNAME)

image:
	docker build -t $(DOCKERTAG) .

push: image
	docker push $(DOCKERTAG)
