project_name = ssr-perf-server-reason-react

DUNE = opam exec -- dune
opam_file = $(project_name).opam

.PHONY: help
help: ## Print this help message
	@echo "";
	@echo "List of available make commands";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: clean
clean: ## Clean artifacts
	$(DUNE) clean

.PHONY: dev
dev: ## Build in watch mode
	$(DUNE) build -w --profile=dev @all

.PHONY: build
build: ## Build the project, including non installable libraries and executables
	$(DUNE) build --profile=dev

.PHONY: build-prod
build-prod: ## Build for production (--profile=prod)
	$(DUNE) build --profile=prod

.PHONY: create-switch
create-switch: ## Create opam switch
	opam switch create . 5.1.1 --deps-only --with-test -y

.PHONY: install
install:
	opam install . --deps-only --with-test --with-doc --with-dev-setup
	cd demo && npm install

.PHONY: pin
pin: ## Pin dependencies
	opam pin add quickjs.dev "https://github.com/ml-in-barcelona/quickjs.ml.git#82044fc532211ac6c7df71fbe879baa2481c9509" -y
	opam pin add server-reason-react.dev "https://github.com/ml-in-barcelona/server-reason-react.git#fb6836045f4ee56cf42c409f2830674146e0eea4" -y

.PHONY: init
init: create-switch pin install ## Create a local dev enviroment

.PHONY: serve
serve: build ## Serve the demo executable
	dune exec _build/default/src/server.exe

.PHONY: serve-prod
serve-prod: build-prod ## Serve the demo executable
	dune exec _build/default/src/server.exe
