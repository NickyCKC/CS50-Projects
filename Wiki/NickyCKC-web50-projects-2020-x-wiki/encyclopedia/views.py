from django.shortcuts import render

from . import util

from django import forms

from markdown2 import Markdown

import random

markdowner = Markdown()


class Search(forms.Form):
    title = forms.CharField(label="Search")


class Create(forms.Form):
    title = forms.CharField(label="Title")
    textarea = forms.CharField(label="Content")


class Edit(forms.Form):
    textarea = forms.CharField(label="Content")


def index(request):
    entries = util.list_entries()
    search_list = []
    if request.method == "POST":
        form = Search(request.POST)
        if form.is_valid():
            title = form.cleaned_data["title"]
            for titles in entries:
                if title in entries:
                    content = util.get_entry(title)
                    content_marked = markdowner.convert(content)
                    return render(request, "encyclopedia/entry.html", {
                        "entry": content_marked,
                        "entryTitle": title,
                        "form": Search()
                    })

                if title.lower() in titles.lower():
                    search_list.append(titles)
            return render(request, "encyclopedia/search.html", {
                "search": search_list,
                "form": Search()
            })
        else:
            return render(request, "encyclopedia/index.html", {
                "form": form
            })

    else:
        return render(request, "encyclopedia/index.html", {
            "entries": util.list_entries(),
            "form": Search()
        })


def entry(request, title):
    content = util.get_entry(title)
    if content is None:
        return render(request, "encyclopedia/error.html", {
            "error": "Requested page was not found"
        })
    else:
        content_marked = markdowner.convert(content)
        return render(request, "encyclopedia/entry.html", {
            "entry": content_marked,
            "entryTitle": title,
            "form": Search()
        })


def create(request):
    if request.method == "POST":
        form = Create(request.POST)
        if form.is_valid():
            title = form.cleaned_data["title"]
            textarea = form.cleaned_data["textarea"]
            entries = util.list_entries()
            if title in entries:
                return render(request, "encyclopedia/error.html", {
                    "form": Search(),
                    "error": "Entry already exists"
                })
            else:
                util.save_entry(title, textarea)
                content = util.get_entry(title)
                content_marked = markdowner.convert(content)
                return render(request, "encyclopedia/entry.html", {
                    "form": Search(),
                    "entry": content_marked,
                    "entryTitle": title
                })
    else:
        return render(request, "encyclopedia/create.html", {
            "form": Search(),
            "create": Create()
        })


def edit(request, title):
    if request.method == "GET":
        content = util.get_entry(title)
        return render(request, "encyclopedia/edit.html", {
            "title": title,
            "content": Edit(initial={"textarea": content}),
            "form": Search()
        })

    else:
        form = Edit(request.POST)
        if form.is_valid():
            textarea = form.cleaned_data["textarea"]
            util.save_entry(title, textarea)
            content = util.get_entry(title)
            content_marked = markdowner.convert(content)
            return render(request, "encyclopedia/entry.html", {
                "entryTitle": title,
                "entry": content_marked,
                "form": Search()
            })


def randompage(request):
    if request.method == "GET":
        entries = util.list_entries()
        no_entries = len(entries) - 1
        random_no = random.randint(0, no_entries)
        entry_no = entries[random_no]
        content = util.get_entry(entry_no)
        content_marked = markdowner.convert(content)
        return render(request, "encyclopedia/entry.html", {
            "entryTitle": entry_no,
            "entry": content_marked,
            "form": Search()
        })